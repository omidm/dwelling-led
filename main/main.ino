#include <OctoWS2811.h>

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF
#define BLACK  0x000000

// Animation configs.
const double kLedRefreshFreq = 50;  // Hz
const double kVerticalRotationFreq = 0.5;  // Hz
const double kRainbowLightnessFreq = 0.5;  // Hz
const double kRainbowHueFreq = 0.01;  // Hz
const double kRainbowMinLightness = 5;  // Lower bound is 0
const double kRainbowMaxLightness = 40;  // Upper bound is 50

// Dwelling measurements and architecture.
const int kMidStripLen = 412;
const int kUpperVerticalStripLen = 40;
const int kLowerVerticalStripLen = 100;
const double kUpperHeightRatio = 0.1;
const int kVerticalStripCount = 6;
const int kMidStripIndex = kVerticalStripCount;
const int kTopStripIndex = kVerticalStripCount + 1;

// Initialize LEDs.
const int kLedsPerStrip = kMidStripLen + kMidStripLen / 5;
DMAMEM int display_memory[kLedsPerStrip * 6];
int drawing_memory[kLedsPerStrip * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(kLedsPerStrip, display_memory, drawing_memory, config);

// Allocate color palette memory.
const int kColorPaletteLen = 200;
int color_palette_1[kColorPaletteLen];

void setup() {
  // Put your setup code here, to run once:
  MakeBiColorPalette(color_palette_1, kColorPaletteLen, BLUE, 15, BLACK);
  leds.begin();

}

void loop() {
  // Put your main code here, to run repeatedly:
  RotateVertical(
      kVerticalRotationFreq, kLedRefreshFreq, kLedsPerStrip,
      color_palette_1, kColorPaletteLen, true /*=move_up*/);
  RotateVertical(
      kVerticalRotationFreq, kLedRefreshFreq, kLedsPerStrip,
      color_palette_1, kColorPaletteLen, false /*=move_up*/);

  RainbowWave(
      kRainbowLightnessFreq, kRainbowHueFreq, kLedRefreshFreq,
      kRainbowMinLightness, kRainbowMaxLightness, true /*red_to_violet*/);
  RainbowWave(
      kRainbowLightnessFreq, kRainbowHueFreq, kLedRefreshFreq,
      kRainbowMinLightness, kRainbowMaxLightness, true /*red_to_violet*/);
}
