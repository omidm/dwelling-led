// This file implements vertical rotation animation.

#include <vector>
#include "metrics.h"

void ShiftVertical(const std::vector<int>& colors,
                   const double color_shift) {
  const int colors_len = colors.size();
  // Set color for the vertical strips.
  for (int led_strip = 0; led_strip < kVerticalStripCount; led_strip++) {
    // Upper segment.
    const double proj_factor_upper =
      kUpperHeightRatio * colors_len / kUpperVerticalStripLen;
    const int led_offset_upper = led_strip * kLedsPerStrip; 
    for (int led_index = 0; led_index < kUpperVerticalStripLen; led_index++) {
      const int color_index =
        (int) (color_shift + led_index * proj_factor_upper) % colors_len;
      leds.setPixel(led_index + led_offset_upper, colors[color_index]);
    }
    // Lower segment.
    const double proj_factor_lower =
      (1 - kUpperHeightRatio) * colors_len / kLowerVerticalStripLen;
    const double color_shift_lower =
      kUpperHeightRatio * colors_len + color_shift;
    const int led_offset_lower =
      kUpperVerticalStripLen + led_strip * kLedsPerStrip;
    for (int led_index = 0; led_index < kLowerVerticalStripLen; led_index++) {
      const int color_index =
        (int) (color_shift_lower + led_index * proj_factor_lower) % colors_len;
      leds.setPixel(led_index + led_offset_lower, colors[color_index]);
    }
  }
  // Set color for the mid strip.
  const int led_offset_mid = kMidStripIndex * kLedsPerStrip;
  const int color_index_mid =
    (int) (color_shift + kUpperHeightRatio * colors_len) % colors_len;
  for (int led_index = 0; led_index < kMidStripLen; led_index++) {
    leds.setPixel(led_index + led_offset_mid, colors[color_index_mid]);
  }
  // Set color for the top strip.
  const int led_offset_top = kTopStripIndex * kLedsPerStrip;
  const int color_index_top =
    (int) (color_shift) % colors_len;
  for (int led_index = 0; led_index < kTopStripLen; led_index++) {
    leds.setPixel(led_index + led_offset_top, colors[color_index_top]);
  }
}

void RotateVertical(const double rotate_freq,
                    const double refresh_freq,
                    const std::vector<int>& colors,
                    const bool move_up) {
  const int colors_len = colors.size();
  const double color_delta =
    colors_len * rotate_freq / refresh_freq;
  if (move_up) {
    for (double color_shift = 0; color_shift < colors_len;
        color_shift += color_delta) {
      ShiftVertical(colors, color_shift);
      leds.show();
      delayMicroseconds(1000000 / refresh_freq);
    }
  } else {
    for (double color_shift = colors_len; color_shift > 0;
        color_shift -= color_delta) {
      ShiftVertical(colors, color_shift);
      leds.show();
      delayMicroseconds(1000000 / refresh_freq);
    }
  }
}
