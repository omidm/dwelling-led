// This file implements color generation.

#include <vector>
#include "metrics.h"

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
  double lightness = kMidLightness;
  const double lightness_step =
    fade_into_black ? -kMidLightness / color_width :
                       kMidLightness / color_width;
  for (int index = 0; index < color_width; index++) {
    colors[(index + shift_index) % colors_len] =
      hsl2rgb(color_hue, kSaturation, lightness);
    lightness += lightness_step;
    SanitizeLightness(&lightness);
  }
  for (int index = color_width; index < colors_len; index++) {
    colors[(index + shift_index) % colors_len] =
      fade_into_black ? BLACK : WHITE;
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

void MakeFadedBiColorPalette(
    const unsigned int color_hue_1, const unsigned int color_hue_2,
    double width_ratio, double shift_ratio,
    const bool fade_into_black,
    unsigned int colors_len, std::vector<int>* colors) {
  SanitizeRatio(&width_ratio);
  SanitizeRatio(&shift_ratio);
  colors->clear();
  colors->resize(colors_len, 0);
  const int color_1_width = colors_len * width_ratio;
  const int color_2_width = colors_len * (1 - width_ratio);
  const int shift_index = colors_len * shift_ratio;
  double lightness = fade_into_black ? kLowLightness :
                                       kHighLightness;
  const double lightness_step =
    fade_into_black ? kMidLightness / color_width :
                     -kMidLightness / color_width;
  for (int index = 0; index < color_1_width / 2; index++) {
    colors[(index + shift_index) % colors_len] =
      hsl2rgb(color_hue_1, kSaturation, lightness);
    lightness += lightness_step;
    SanitizeLightness(&lightness);
  }
  for (int index = color_1_width / 2; index < color_1_width; index++) {
    colors[(index + shift_index) % colors_len] =
      hsl2rgb(color_hue_1, kSaturation, lightness);
    lightness -= lightness_step;
    SanitizeLightness(&lightness);
  }
  for (int index = 0; index < color_2_width / 2; index++) {
    colors[(index + color_1_width + shift_index) % colors_len] =
      hsl2rgb(color_hue_2, kSaturation, lightness);
    lightness += lightness_step;
    SanitizeLightness(&lightness);
  }
  for (int index = color_2_width / 2; index < color_2_width; index++) {
    colors[(index + color_1_width + shift_index) % colors_len] =
      hsl2rgb(color_hue_2, kSaturation, lightness);
    lightness -= lightness_step;
    SanitizeLightness(&lightness);
  }
}

void MakeRainbowPalette(
    const unsigned int min_hue,
    const unsigned int max_hue,
    const unsigned int saturation,
    const unsigned int lightness,
    double shift_ratio,
    unsigned int colors_len, std::vector<int>* colors) {
  SanitizeRatio(&shift_ratio);
  SanitizeHue(&min_hue);
  SanitizeHue(&max_hue);
  colors->clear();
  colors->resize(colors_len, 0);
  const double hue_delta =
    (double) (max_hue - min_hue) / (double) (colors_len);
  const int shift_index = colors_len * shift_ratio;
  double hue = min_hue;
  for (int index = 0; index < color_len; index++) {
    colors[(index + shift_index) % colors_len] =
      hsl2rgb(hue, saturation, lightness);
    hue += hue_delta;
    SanitizeHue(&hue);
  }
}
