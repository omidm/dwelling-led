// This file implements rainbow wave animation.

#include "metrics.h"

#define MAX_HUE 360
#define SATURATION 100

void WaveLightness(const double lightness_freq,
                   const double refresh_freq,
                   const double min_lightness,
                   const double max_lightness,
                   const double hue) {
  const double lightness_delta =
    (max_lightness - min_lightness) * lightness_freq / refresh_freq * 2;
  // Light up;
  for (double lightness = min_lightness; lightness < max_lightness;
      lightness += lightness_delta) {
    const int color = hsl2rgb(hue, SATURATION, lightness);
    for (int i = 0; i < leds.numPixels(); i++) {
      leds.setPixel(i, color);
    }
    leds.show();
    delayMicroseconds(1000000 / refresh_freq);
  }
  // Light down;
  for (double lightness = max_lightness; lightness > min_lightness;
      lightness -= lightness_delta) {
    const int color = hsl2rgb(hue, SATURATION, lightness);
    for (int i = 0; i < leds.numPixels(); i++) {
      leds.setPixel(i, color);
    }
    leds.show();
    delayMicroseconds(1000000 / refresh_freq);
  }
}

void RainbowWave(const double lightness_freq,
                 const double hue_freq,
                 const double refresh_freq,
                 const double min_lightness,
                 const double max_lightness,
                 const bool red_to_violet) {
  const double hue_delta =
    MAX_HUE * hue_freq / lightness_freq;
  if (red_to_violet) {
    for (double hue = 0; hue < MAX_HUE; hue += hue_delta) {
      WaveLightness(
          lightness_freq, refresh_freq, min_lightness, max_lightness, hue);
    }
  } else {
    for (double hue = MAX_HUE; hue > 0; hue -= hue_delta) {
      WaveLightness(
          lightness_freq, refresh_freq, min_lightness, max_lightness, hue);
    }
  }
}
