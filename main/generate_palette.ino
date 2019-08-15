// This file implements color generation.

void MakeBiColorPalette(
    int* colors, const int colors_len,
    const int segment_color, const int segment_width, const int rest_color) {
  for (int index = 0; index < segment_width && index < colors_len; index++) {
    colors[index] = segment_color;
  }
  for (int index = segment_width; index < colors_len; index++) {
    colors[index] = rest_color;
  }
}
