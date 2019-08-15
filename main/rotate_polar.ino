// This file implements polar rotation animation.

void ShiftPolar(const int leds_per_strip,
                const int* colors,
                const int colors_len,
                const double color_shift) {
  // Set color for the vertical strips.
  for (int led_strip = 0; led_strip < kVerticalStripCount; led_strip++) {
    const int led_offset_vertical = led_strip * leds_per_strip; 
    const int color_index =
      (int) (color_shift + kStripPolarPosition[led_strip] * color_len) % colors_len;
    for (int led_index = 0; led_index < kVerticalStripLen; led_index++) {
      leds.setPixel(led_index + led_offset_vertical, colors[color_index]);
    }
  }
  // Set color for the mid strip.
  const double proj_factor_mid = colors_len / kAugMidStripLen;
  const double led_offset_mid = kMidStripIndex * leds_per_strip; 
  for (int led_index = 0; led_index < kMidStripLen; led_index++) {
    const int color_index =
      (int) (color_shift + led_index * proj_factor_mid) % colors_len;
    leds.setPixel(led_index + led_offset_mid, colors[color_index]);
  }
  // Set color for the top strip.
  const double proj_factor_top = colors_len / kTopStripLen;
  const double led_offset_top = kTopStripIndex * leds_per_strip; 
  for (int led_index = 0; led_index < kTopStripLen; led_index++) {
    const int color_index =
      (int) (color_shift + led_index * proj_factor_top) % colors_len;
    leds.setPixel(led_index + led_offset_top, colors[color_index]);
  }
}

void RotatePolar(const double rotate_freq,
                 const double refresh_freq,
                 const int leds_per_strip,
                 const int* colors,
                 const int colors_len,
                 const bool clockwise) {
  const double color_delta =
    colors_len * rotate_freq / refresh_freq;
  if (clockwise) {
    for (double color_shift = 0; color_shift < colors_len;
        color_shift += color_delta) {
      ShiftPolar(leds_per_strip, colors, colors_len, color_shift);
      leds.show();
      delayMicroseconds(1000000 / refresh_freq);
    }
  } else {
    for (double color_shift = colors_len; color_shift > 0;
        color_shift -= color_delta) {
      ShiftPolar(leds_per_strip, colors, colors_len, color_shift);
      leds.show();
      delayMicroseconds(1000000 / refresh_freq);
    }
  }
}
