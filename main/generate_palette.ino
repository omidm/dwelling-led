// This file implements color generation.

#include <vector>

void MakeMonoColorPalette(
    const int color, unsigned int colors_len, std::vector<int>* colors) {
  if (colors_len == 0) {
    colors_len = 1;
  }
  colors->clear();
  colors->resize(colors_len, 0);
  for (int index = 0; index < colors_len; index++) {
    colors[index] = color;
  }
}

void MakeBiColorPalette(
    const int color_1, const int color_2, double split_ratio,
    unsigned int colors_len, std::vector<int>* colors) {
  if (split_ratio < 0 || split_ratio > 1) {
    split_ratio = 1;
  }
  if (colors_len == 0) {
    colors_len = 1;
  }
  colors->clear();
  colors->resize(colors_len, 0);
  const int color_1_width = colors_len * split_ratio;
  for (int index = 0; index < color_1_width; index++) {
    colors[index] = color_1;
  }
  for (int index = color_1_width; index < colors_len; index++) {
    colors[index] = color_2;
  }
}
