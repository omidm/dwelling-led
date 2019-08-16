
#include <OctoWS2811.h>
#include "vector.h"
#include "metrics.h"

// Initialize LEDs.
DMAMEM int display_memory[kLedsPerStrip * 6];
int drawing_memory[kLedsPerStrip * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(kLedsPerStrip, display_memory, drawing_memory, config);

// Color palettes to be initialized in setup.
std::vector<int> color_palette_1;
std::vector<int> color_palette_2;
std::vector<int> color_palette_3;
std::vector<int> color_palette_4;
std::vector<int> color_palette_5;
std::vector<int> color_palette_6;

void setup() {
  // Put your setup code here, to run once:
  MakeMonoColorPalette(
      RED /*=color*/,
      100 /*=colors_len*/, &color_palette_1);
  MakeFadedMonoColorPalette(
      120 /*=color_hue*/,
      0.2 /*=width_ratio*/, 0 /*=shift_ratio*/,
      true /*=fade_into_black*/,
      100 /*=colors_len*/, &color_palette_2);
  MakeBiColorPalette(
      BLUE /*=color_1*/, BLACK /*=color_2*/,
      0.2 /*=width_ratio*/, 0 /*=shift_ratio*/,
      100 /*=colors_len*/, &color_palette_3);
  MakeFadedBiColorPalette(
      120 /*=color_hue_1*/, 210 /*=color_hue_2*/,
      0.5 /*=width_ratio*/, 0 /*=shift_ratio*/,
      false /*=fade_into_black*/,
      100 /*=colors_len*/, &color_palette_4);
  MakeHueSweepPalette(
      0 /*=min_hue*/, 360 /*=max_hue*/,
      kSaturation /*=saturation*/,
      kMidLightness /*=lightness*/,
      0 /*=shift_ratio*/,
      100 /*=colors_len*/, &color_palette_5);
  MakeLightnessSweepPalette(
      180 /*=hue*/,
      kSaturation /*=saturation*/,
      0 /*=min_lightness*/, 100 /*=max_lightness*/,
      0 /*=shift_ratio*/,
      100 /*=colors_len*/, &color_palette_6);
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
      kLowLightness, kMidLightness, true /*=red_to_violet*/);
  RainbowWave(
      kRainbowLightnessFreq, kRainbowHueFreq, kLedRefreshFreq,
      kLowLightness, kMidLightness, false /*=red_to_violet*/);
}
