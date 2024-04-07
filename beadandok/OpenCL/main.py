import numpy as np
import pyopencl as cl
import time
import imageio


def current_timestamp_ms():
    return int(round(time.time() * 1000))


def compute_kernel(radius):
    kernel_diameter = radius * 2 + 1
    sigma = radius / 3.0
    s = 2.0 * sigma * sigma
    sum_val = 0.0
    kernel = np.zeros((kernel_diameter, kernel_diameter), dtype=np.float32)
    for i in range(-radius, radius + 1):
        for j in range(-radius, radius + 1):
            r = np.sqrt(i ** 2 + j ** 2)
            kernel[i + radius, j + radius] = np.exp(-r ** 2 / s) / np.sqrt(np.pi * s)
            sum_val += kernel[i + radius, j + radius]
    kernel /= sum_val
    return kernel.flatten()


def blur_image_opencl(input_image, width, height, radius):

    start_time = current_timestamp_ms()
    platform = cl.get_platforms()[0]
    device = platform.get_devices()[0]
    context = cl.Context([device])
    queue = cl.CommandQueue(context)

    # Kernel code CONTINUE
    kernel_code = """
    __kernel void gaussian_blur(const int width, const int height, const int radius, __global const float *input, __global float *output, __global float *blur_kernel) {
        
        int x = get_global_id(0);
        int y = get_global_id(1);
        if (x >= width || y >= height) return;
        
        float sum = 0.0;
        int kernel_diameter = 2 * radius + 1;
        for (int ky = -radius; ky <= radius; ky++) {
            for (int kx = -radius; kx <= radius; kx++) {
                int nx = x + kx;
                int ny = y + ky;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    float value = input[ny * width + nx];
                    float weight = blur_kernel[(ky + radius) * kernel_diameter + (kx + radius)];
                    sum += value * weight;
                }
            }
        }
        output[y * width + x] = sum;
    }
    """

    kernel = compute_kernel(radius)
    mf = cl.mem_flags


    program = cl.Program(context, kernel_code).build()

    input_buf = cl.Buffer(context, mf.READ_ONLY | mf.COPY_HOST_PTR, hostbuf=input_image)
    output_buf = cl.Buffer(context, mf.WRITE_ONLY, input_image.nbytes)
    kernel_buf = cl.Buffer(context, mf.READ_ONLY | mf.COPY_HOST_PTR, hostbuf=kernel)

    end_time = current_timestamp_ms()
    print(f"Initialization: {end_time - start_time} ms")
    start_time = current_timestamp_ms()
    gaussian_blur = program.gaussian_blur
    gaussian_blur(queue, (width, height), None, np.int32(width), np.int32(height), np.int32(radius), input_buf,
                  output_buf, kernel_buf)

    result = np.empty_like(input_image)
    cl.enqueue_copy(queue, result, output_buf).wait()
    end_time = current_timestamp_ms()
    print(f"Execution: {end_time - start_time} ms")
    return result


def main():
    radius = 20
    width, height = 640, 480
    input_image = np.random.rand(height, width).astype(np.float32)

    output_image = blur_image_opencl(input_image, width, height, radius)

    # save it

    output_image_normalized = (
                (output_image - output_image.min()) / (output_image.max() - output_image.min()) * 255).astype(np.uint8)

    imageio.imwrite('blurred_image.png', output_image_normalized)
    print("Image saved as blurred_image.png")


if __name__ == "__main__":
    main()
