// This file implements polar rotation animation.

#include "vector.h"
#include "metrics.h"

void ShiftPolar(const std::vector<int>& colors,
                const double color_shift) {
  const int colors_len = colors.size();
  // Set color for the vertical strips.
  for (int led_strip = 0; led_strip < kVerticalStripCount; led_strip++) {
    const int led_offset_vertical = led_strip * kLedsPerStrip; 
    const int color_index =
      (int) (color_shift + kStripPolarPositions[led_strip] * colors_len) % colors_len;
    for (int led_index = 0; led_index < kVerticalStripLen; led_index++) {
      leds[led_index + led_offset_vertical] = colors[color_index];
    }
  }
  // Set color for the mid strip.
  const double proj_factor_mid = colors_len / kAugMidStripLen;
  const double led_offset_mid = kMidStripIndex * kLedsPerStrip; 
  for (int led_index = 0; led_index < kMidStripLen; led_index++) {
    const int color_index =
      (int) (color_shift + led_index * proj_factor_mid) % colors_len;
    leds[led_index + (int)led_offset_mid] = colors[color_index];
  }
  // Set color for the top strip.
  const double proj_factor_top = colors_len / kTopStripLen;
  const double led_offset_top = kTopStripIndex * kLedsPerStrip; 
  for (int led_index = 0; led_index < kTopStripLen; led_index++) {
    const int color_index =
      (int) (color_shift + led_index * proj_factor_top) % colors_len;
    leds[led_index + (int)led_offset_top] = colors[color_index];
  }
}

void RotatePolar(const double rotate_freq,
                 const double refresh_freq,
                 const std::vector<int>& colors,
                 const bool clockwise) {
  const int colors_len = colors.size();
  const double color_delta =
    colors_len * rotate_freq / refresh_freq;
  if (clockwise) {
    for (double color_shift = 0; color_shift < colors_len;
        color_shift += color_delta) {
      ShiftPolar(colors, color_shift);
      FastLED.show();
      FastLED.delay(1000 / refresh_freq);
    }
  } else {
    for (double color_shift = colors_len; color_shift > 0;
        color_shift -= color_delta) {
      ShiftPolar(colors, color_shift);
      FastLED.show();
      FastLED.delay(1000 / refresh_freq);
    }
  }
}
