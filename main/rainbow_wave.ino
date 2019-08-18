// This file implements rainbow wave animation.

#include "metrics.h"

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
    const int color = hsl2rgb(hue, kSaturation, lightness);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = color;
    }
    FastLED.show();
    FastLED.delay(1000 / refresh_freq);
  }
  // Light down;
  for (double lightness = max_lightness; lightness > min_lightness;
      lightness -= lightness_delta) {
    const int color = hsl2rgb(hue, kSaturation, lightness);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = color;
    }
    FastLED.show();
    FastLED.delay(1000 / refresh_freq);
  }
}

void RainbowWave(const double lightness_freq,
                 const double hue_freq,
                 const double refresh_freq,
                 const double min_lightness,
                 const double max_lightness,
                 const bool red_to_violet) {
  const double hue_delta =
    kMaxHue * hue_freq / lightness_freq;
  if (red_to_violet) {
    for (double hue = 0; hue < kMaxHue; hue += hue_delta) {
      WaveLightness(
          lightness_freq, refresh_freq, min_lightness, max_lightness, hue);
    }
  } else {
    for (double hue = kMaxHue; hue > 0; hue -= hue_delta) {
      WaveLightness(
          lightness_freq, refresh_freq, min_lightness, max_lightness, hue);
    }
  }
}
