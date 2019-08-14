#include <OctoWS2811.h>

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF
#define BLACK  0x000000


const double kLedRefreshRate = 50;  // Hzt
const double kUpperHeightRatio = 0.1;

const int kMidStripLen = 412;
const int kUpperVerticalStripLen = 40;
const int kLowerVerticalStripLen = 100;
const int kVerticalStripLen = kUpperVerticalStripLen + kLowerVerticalStripLen;

const int kVerticalStripCount = 6;
const int kMidStripIndex = kVerticalStripCount;
const int kTopStripIndex = kVerticalStripCount + 1;


const int kLedsPerStrip = 412;

DMAMEM int display_memory[kLedsPerStrip*6];
int drawing_memory[kLedsPerStrip*6];
const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(kLedsPerStrip, display_memory, drawing_memory, config);


const int kColorsLength = kVerticalStripLen;
const int kColorWidth = 15;
int Colors[kColorsLength];

void MakeColors() {
  for (int index = 0; index < kColorsLength; index++) {
    Colors[index] = BLACK;
  }
  for (int index = 0; index < kColorWidth; index++) {
    Colors[index] = BLUE;
  }
  /*
  Colors[0] = RED;
  Colors[1] = GREEN;
  Colors[2] = BLUE;
  Colors[3] = YELLOW;
  Colors[4] = ORANGE;
  */
}


void ShiftVertical(const int* colors,
                   const int colors_len,
                   const double color_shift) {
  // Set color for the vertical strips.
  for (int led_strip = 0; led_strip < kVerticalStripCount; led_strip++) {
    // Upper segment.
    const double proj_factor_upper =
      kUpperHeightRatio * colors_len / kUpperVerticalStripLen;
    const double color_shift_upper = color_shift;
    const int led_offset_upper = led_strip * kLedsPerStrip; 
    for (int led_index = 0; led_index < kUpperVerticalStripLen; led_index++) {
      const int color_index =
        (int) (color_shift_upper + led_index * proj_factor_upper) % colors_len;
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
  for (int led_index = 0; led_index < kMidStripLen; led_index++) {
    const int color_index =
      (int) (color_shift + kUpperHeightRatio * colors_len) % colors_len;
    leds.setPixel(led_index + kMidStripIndex*kLedsPerStrip, colors[color_index]);
  }
  // Set color for the top strip.
  for (int led_index = 0; led_index < kLedsPerStrip; led_index++) {
    const int color_index =
      (int) (color_shift) % colors_len;
    leds.setPixel(led_index + kTopStripIndex*kLedsPerStrip, Colors[color_index]);
  }
}

void RotateVertical(const double rotate_freq,
                    const double refresh_freq,
                    const int* colors,
                    const int colors_len) {
  const double color_delta =
    colors_len * rotate_freq / refresh_freq * 2;
  // Move up;
  for (double color_shift = 0; color_shift < colors_len;
       color_shift += color_delta) {
    ShiftVertical(colors, colors_len, color_shift);
    leds.show();
    delayMicroseconds(1000000 / refresh_freq);
  }
  // Move down;
  for (double color_shift = colors_len; color_shift > 0;
       color_shift -= color_delta) {
    ShiftVertical(colors, colors_len, color_shift);
    leds.show();
    delayMicroseconds(1000000 / refresh_freq);
  }
}

void setup() {
  // Put your setup code here, to run once:
  MakeColors();
  leds.begin();

}

void loop() {
  // Put your main code here, to run repeatedly:
  RotateVertical(.5, kLedRefreshRate, Colors, kColorsLength);
}
