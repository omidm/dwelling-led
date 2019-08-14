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
    for (int led_index = 0; led_index < kUpperVerticalStripLen; led_index++) {
      const int color_index =
        (color_shift + led_index / kUpperVerticalStripLen * kUpperHeightRatio * colors_len) % colors_len;
      leds.setPixel(led_index + led_strip*kLedsPerStrip, colors[color_index]);
    }
    const double color_shift_lower = kUpperHeightRatio * colors_len;
    for (int led_index = kUpperVerticalStripLen; led_index < kVerticalStripLen; led_index++) {
      const int color_index =
        (color_shift + color_shift_lower + (led_index - kUpperVerticalStripLen) / kLowerVerticalStripLen * (1 - kUpperHeightRatio) * colors_len) % colors_len;
      leds.setPixel(led_index + led_strip*kLedsPerStrip, colors[color_index]);
    }
  }
  // Set color for the mid strip.
  for (int led_index = 0; led_index < kMidStripLen; led_index++) {
    const int color_index =
      (color_shift + kUpperHeightRatio * colors_len) % colors_len;
    leds.setPixel(led_index + kMidStripIndex*kLedsPerStrip, colors[color_index]);
  }
  // Set color for the top strip.
  for (int led_index = 0; led_index < kLedsPerStrip; led_index++) {
    const int color_index =
      (color_shift) % colors_len;
    leds.setPixel(led_index + kTopStripIndex*kLedsPerStrip, Colors[color_index]);
  }
}

void RotateVertical(const double freq,
                    const int* colors,
                    const int colors_len) {
  const double color_delta = color_len * freq / kLedRefreshRate * 2;
  // Move up;
  for (double color_shift = 0; color_shift < color_len;
       color_shift += color_delta) {
    ShiftVertical(colors, colors_len, color_shift);
    leds.show();
    delayMicroseconds(1000000 / kLedRefreshRate);
  }
  // Move down;
  for (double color_shift = color_len; color_shift > 0;
       color_shift -= color_delta) {
    ShiftVertical(colors, colors_len, color_shift);
    leds.show();
    delayMicroseconds(1000000 / kLedRefreshRate);
  }
}

void setup() {
  // put your setup code here, to run once:
  MakeColors();
  leds.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  RotateVertical(.5, &Colors, kColorsLength);
}
