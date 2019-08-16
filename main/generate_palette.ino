// This file implements color generation.

#include <vector>

void MakeMonoColorPalette(
    const int color,
    unsigned int colors_len, std::vector<int>* colors) {
  colors->clear();
  colors->resize(colors_len, 0);
  for (int index = 0; index < colors_len; index++) {
    colors[index] = color;
  }
}

void MakeFadedMonoColorPalette(
    const unsigned int color_hue,
    double width_ratio, double shift_ratio,
    const bool fade_into_black,
    unsigned int colors_len, std::vector<int>* colors) {
  SanitizeRatio(&width_ratio);
  SanitizeRatio(&shift_ratio);
  colors->clear();
  colors->resize(colors_len, 0);
  const int color_width = colors_len * width_ratio;
  const int shift_index = colors_len * shift_ratio;
  double lightness = 50.0;
  const double lightness_step =
    fade_into_black ? -50.0 / color_width : 50.0 / color_width;
  for (int index = 0; index < color_width; index++) {
    colors[(index + shift_index) % colors_len] = hsl2rgb(hue, 100, lightness);
    lightness += lightness_step;
    if (lightness < 0) {
      lightness = 0;
    } else if (lightness > 100) {
      lightness = 100;
    }
  }
  for (int index = color_width; index < colors_len; index++) {
    colors[(index + shift_index) % colors_len] =
      fade_into_black ? hsl2rgb(hue, 100, 0) : hsl2rgb(hue, 100, 100);
  }
}

void MakeBiColorPalette(
    const int color_1, const int color_2,
    double width_ratio, double shift_ratio,
    unsigned int colors_len, std::vector<int>* colors) {
  SanitizeRatio(&width_ratio);
  SanitizeRatio(&shift_ratio);
  colors->clear();
  colors->resize(colors_len, 0);
  const int color_1_width = colors_len * width_ratio;
  const int shift_index = colors_len * shift_ratio;
  for (int index = 0; index < color_1_width; index++) {
    colors[(index + shift_index) % colors_len] = color_1;
  }
  for (int index = color_1_width; index < colors_len; index++) {
    colors[(index + shift_index) % colors_len] = color_2;
  }
}
