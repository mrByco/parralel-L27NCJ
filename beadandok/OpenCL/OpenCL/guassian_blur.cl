__kernel void gaussian_blur(const int width, const int height, const int radius,
                            __global const float *input, __global float *output,
                            __global float *blur_kernel) {

  int x = get_global_id(0);
  int y = get_global_id(1);
  if (x >= width || y >= height)
    return;

  float sum = 0.0;
  int kernel_diameter = 2 * radius + 1;
  for (int ky = -radius; ky <= radius; ky++) {
    for (int kx = -radius; kx <= radius; kx++) {
      int nx = x + kx;
      int ny = y + ky;
      if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        float value = input[ny * width + nx];
        float weight =
            blur_kernel[(ky + radius) * kernel_diameter + (kx + radius)];
        sum += value * weight;
      }
    }
  }
  output[y * width + x] = sum;
}