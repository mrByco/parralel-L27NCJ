import numpy as np
import pyopencl as cl
import time
import imageio


def current_timestamp_ms():
    return int(round(time.time() * 1000))


def compute_kernel_1d(radius):
    kernel_length = radius * 2 + 1
    sigma = radius / 3.0
    s = 2.0 * sigma * sigma
    sum_val = 0.0
    kernel = np.zeros(kernel_length, dtype=np.float32)
    for i in range(-radius, radius + 1):
        r = np.abs(i)
        kernel[i + radius] = np.exp(-r ** 2 / s) / (np.pi * s)
        sum_val += kernel[i + radius]
    kernel /= sum_val
    return kernel


def blur_image_opencl_separable(input_image, width, height, radius):
    start_time = current_timestamp_ms()
    platform = cl.get_platforms()[0]
    device = platform.get_devices()[0]
    context = cl.Context([device])
    queue = cl.CommandQueue(context)

    # Kernel code for horizontal pass
    kernel_code_h = """
    __kernel void gaussian_blur_horizontal(const int width, const int height, const int radius, __global const float *input, __global float *output, __global const float *blur_kernel) {

        int x = get_global_id(0);
        int y = get_global_id(1);
        if (y >= height) return;

        float sum = 0.0;
        int kernel_length = 2 * radius + 1;
        for (int kx = -radius; kx <= radius; kx++) {
            int nx = x + kx;
            if (nx >= 0 && nx < width) {
                float value = input[y * width + nx];
                float weight = blur_kernel[kx + radius];
                sum += value * weight;
            }
        }
        output[y * width + x] = sum;
    }
    """

    # Kernel code for vertical pass (similar structure to horizontal pass but iterating over y)
    kernel_code_v = """
    __kernel void gaussian_blur_vertical(const int width, const int height, const int radius, __global const float *input, __global float *output, __global const float *blur_kernel) {

        int x = get_global_id(0);
        int y = get_global_id(1);
        if (x >= width) return;

        float sum = 0.0;
        int kernel_length = 2 * radius + 1;
        for (int ky = -radius; ky <= radius; ky++) {
            int ny = y + ky;
            if (ny >= 0 && ny < height) {
                float value = input[ny * width + x];
                float weight = blur_kernel[ky + radius];
                sum += value * weight;
            }
        }
        output[y * width + x] = sum;
    }
    """

    kernel_1d = compute_kernel_1d(radius)
    mf = cl.mem_flags
    intermediate_image = np.empty_like(input_image)

    # Horizontal pass
    program_h = cl.Program(context, kernel_code_h).build()
    program_v = cl.Program(context, kernel_code_v).build()
    input_buf = cl.Buffer(context, mf.READ_ONLY | mf.COPY_HOST_PTR, hostbuf=input_image)
    intermediate_buf = cl.Buffer(context, mf.WRITE_ONLY, input_image.nbytes)
    kernel_buf = cl.Buffer(context, mf.READ_ONLY | mf.COPY_HOST_PTR, hostbuf=kernel_1d)
    output_buf = cl.Buffer(context, mf.WRITE_ONLY, intermediate_image.nbytes)

    start_time_compute = current_timestamp_ms()
    program_h.gaussian_blur_horizontal(queue, (width, height), None, np.int32(width), np.int32(height),
                                       np.int32(radius), input_buf, intermediate_buf, kernel_buf)
    cl.enqueue_copy(queue, intermediate_image, intermediate_buf).wait()

    intermediate_buf = cl.Buffer(context, mf.READ_ONLY | mf.COPY_HOST_PTR, hostbuf=intermediate_image)
    program_v.gaussian_blur_vertical(queue, (width, height), None, np.int32(width), np.int32(height), np.int32(radius),
                                     intermediate_buf, output_buf, kernel_buf)

    result = np.empty_like(input_image)
    cl.enqueue_copy(queue, result, output_buf).wait()

    end_time_compute = current_timestamp_ms()
    print(f"Execution: {end_time_compute - start_time_compute} ms")

    end_time = current_timestamp_ms()
    print(f"Total Execution: {end_time - start_time} ms")
    return result


def main():
    radius = 50
    width, height = 6400, 4800
    input_image = np.random.rand(height, width).astype(np.float32)

    output_image = blur_image_opencl_separable(input_image, width, height, radius)

    # Normalize and save the image
    output_image_normalized = (
                (output_image - output_image.min()) / (output_image.max() - output_image.min()) * 255).astype(np.uint8)
    imageio.imwrite('blurred_image_separable.png', output_image_normalized)
    print("Image saved as blurred_image_separable.png")


if __name__ == "__main__":
    main()
