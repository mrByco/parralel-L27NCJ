import os
import sys
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
    #print(f"Using platform: {platform.name}")
    device = platform.get_devices()[0]
    #print(f"Using device: {device.name}")
    context = cl.Context([device])
    queue = cl.CommandQueue(context)

    # Kernel code CONTINUE
    cl_kernel_code = open('guassian_blur.cl', 'r').read()

    kernel = compute_kernel(radius)
    mf = cl.mem_flags


    program = cl.Program(context, cl_kernel_code).build()

    input_buf = cl.Buffer(context, mf.READ_ONLY | mf.COPY_HOST_PTR, hostbuf=input_image)
    output_buf = cl.Buffer(context, mf.WRITE_ONLY, input_image.nbytes)
    kernel_buf = cl.Buffer(context, mf.READ_ONLY | mf.COPY_HOST_PTR, hostbuf=kernel)

    end_time = current_timestamp_ms()
    #print(f"Initialization: {end_time - start_time} ms")
    start_time = current_timestamp_ms()
    gaussian_blur = program.gaussian_blur
    gaussian_blur(queue, (width, height), None, np.int32(width), np.int32(height), np.int32(radius), input_buf,
                  output_buf, kernel_buf)

    result = np.empty_like(input_image)
    cl.enqueue_copy(queue, result, output_buf).wait()
    end_time = current_timestamp_ms()
    #print(f"Execution: {end_time - start_time} ms")
    print(f"{end_time - start_time}")
    return result


def main():
    # get args, resolution radois and threads

    os.chdir(sys.path[0])   
    
    if len(sys.argv) != 4:
        print("Usage: python main.py <radious> <radius> <threads>")
        print("Threads are not just there for the interface (compare to cpu version)")
        sys.exit(1)
    
    radius = int(sys.argv[2])
    int("15")
    width, height = int(sys.argv[1]), int(sys.argv[1])
    input_image = np.random.rand(height, width).astype(np.float32)

    output_image = blur_image_opencl(input_image, width, height, radius)

    # save it

    output_image_normalized = (
                (output_image - output_image.min()) / (output_image.max() - output_image.min()) * 255).astype(np.uint8)

    imageio.imwrite('blurred_image.png', output_image_normalized)
    #print("Image saved as blurred_image.png")


if __name__ == "__main__":
    main()
