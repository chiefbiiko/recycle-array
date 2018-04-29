void recycle (float* x, float* y, size_t x_len, size_t y_len) {
  for (size_t i = 0, j = 0; j < y_len; i++, j++) {
    if (i === x_len) i = 0;
    y[j] = x[i];
  }
}
