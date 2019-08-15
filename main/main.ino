
#include <vector>
#include <OctoWS2811.h>
#include "metrics.h"

// Initialize LEDs.
DMAMEM int display_memory[kLedsPerStrip * 6];
int drawing_memory[kLedsPerStrip * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(kLedsPerStrip, display_memory, drawing_memory, config);

// Color palettes to be initialized in setup.
std::vector<int> color_palette_1;

void setup() {
  // Put your setup code here, to run once:
  MakeBiColorPalette(BLUE, BLACK, 100, 0.1, &color_palette_1);
  leds.begin();
}

void loop() {
  // Put your main code here, to run repeatedly:
  RotateVertical(
      kVerticalRotationFreq, kLedRefreshFreq,
      color_palette_1, true /*=move_up*/);
  RotateVertical(
      kVerticalRotationFreq, kLedRefreshFreq,
      color_palette_1, false /*=move_up*/);

  RotatePolar(
      kPolarRotationFreq, kLedRefreshFreq,
      color_palette_1, true /*=clockwise*/);
  RotatePolar(
      kPolarRotationFreq, kLedRefreshFreq,
      color_palette_1, false /*=clockwise*/);

  RainbowWave(
      kRainbowLightnessFreq, kRainbowHueFreq, kLedRefreshFreq,
      kRainbowMinLightness, kRainbowMaxLightness, true /*red_to_violet*/);
  RainbowWave(
      kRainbowLightnessFreq, kRainbowHueFreq, kLedRefreshFreq,
      kRainbowMinLightness, kRainbowMaxLightness, true /*red_to_violet*/);
}
