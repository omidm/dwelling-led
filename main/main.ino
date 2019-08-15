
#include <OctoWS2811.h>
#include "metrics.h"

// Initialize LEDs.
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
      kVerticalRotationFreq, kLedRefreshFreq,
      color_palette_1, kColorPaletteLen, true /*=move_up*/);
  RotateVertical(
      kVerticalRotationFreq, kLedRefreshFreq,
      color_palette_1, kColorPaletteLen, false /*=move_up*/);

  RotatePolar(
      kPolarRotationFreq, kLedRefreshFreq,
      color_palette_1, kColorPaletteLen, true /*=clockwise*/);
  RotatePolar(
      kPolarRotationFreq, kLedRefreshFreq,
      color_palette_1, kColorPaletteLen, false /*=clockwise*/);

  RainbowWave(
      kRainbowLightnessFreq, kRainbowHueFreq, kLedRefreshFreq,
      kRainbowMinLightness, kRainbowMaxLightness, true /*red_to_violet*/);
  RainbowWave(
      kRainbowLightnessFreq, kRainbowHueFreq, kLedRefreshFreq,
      kRainbowMinLightness, kRainbowMaxLightness, true /*red_to_violet*/);
}
