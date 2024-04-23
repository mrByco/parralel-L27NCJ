import os
import sys
import numpy as np
import pyopencl as cl
import time
import imageio


def current_timestamp_ms():
    return int(round(time.time() * 1000))


def run_x_times_bench(times: [int]):

    start_time = current_timestamp_ms()
    platform = cl.get_platforms()[0]
    #print(f"Using platform: {platform.name}")
    device = platform.get_devices()[0]
    #print(f"Using device: {device.name}")
    context = cl.Context([device])
    queue = cl.CommandQueue(context)

    cl_kernel_code = open('x_times.cl', 'r').read()

    mf = cl.mem_flags


    program = cl.Program(context, cl_kernel_code).build()


    end_time = current_timestamp_ms()
    #print(f"Initialization: {end_time - start_time} ms")
    start_time = current_timestamp_ms()
    x_times = program.x_times
    x_times(queue, (50000000, 22), None, np.int32(400000))

    queue.finish();
    end_time = current_timestamp_ms()

    print(f"{end_time - start_time}")


def main():
    # get args, resolution radois and threads

    os.chdir(sys.path[0])   
    run_x_times_bench([100])
    #print("Image saved as blurred_image.png")


if __name__ == "__main__":
    main()
