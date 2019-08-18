
#define USE_OCTOWS2811

#include <OctoWS2811.h>
#include <FastLED.h>
#include "vector.h"
#include "trng.h"
#include "metrics.h"

// allocate memory for leds
CRGB leds[kLedsPerStrip * 6];

// Random number to be loaded in setup and used to pick the animation.
uint32_t random_number;

// Color palettes to be initialized in setup.
std::vector<int> color_palette_1;
std::vector<int> color_palette_2;
std::vector<int> color_palette_3;
std::vector<int> color_palette_4;
std::vector<int> color_palette_5;
std::vector<int> color_palette_6;

void setup()
{
    // initialize fast led with octows2811 controller
    FastLED.addLeds<OCTOWS2811>(leds, kLedsPerStrip);
    FastLED.setBrightness(32); // adjust brightness here!

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

    // Setup RNG
    SIM_SCGC6 |= SIM_SCGC6_RNGA; // enable RNG
    RNG_CR &= ~RNG_CR_SLP_MASK;
    RNG_CR |= RNG_CR_HA_MASK; // high assurance, not needed
    random_number = trng();
}

void loop()
{
    // Put your main code here, to run repeatedly:
    switch (random_number % 3)
    {
    case 0:
        RotateVertical(
            kVerticalRotationFreq, kLedRefreshFreq,
            color_palette_1, true /*=move_up*/);
        RotateVertical(
            kVerticalRotationFreq, kLedRefreshFreq,
            color_palette_1, false /*=move_up*/);
    case 1:
        RotatePolar(
            kPolarRotationFreq, kLedRefreshFreq,
            color_palette_1, true /*=clockwise*/);
        RotatePolar(
            kPolarRotationFreq, kLedRefreshFreq,
            color_palette_1, false /*=clockwise*/);
    case 3:
        RainbowWave(
            kRainbowLightnessFreq, kRainbowHueFreq, kLedRefreshFreq,
            kLowLightness, kMidLightness, true /*=red_to_violet*/);
        RainbowWave(
            kRainbowLightnessFreq, kRainbowHueFreq, kLedRefreshFreq,
            kLowLightness, kMidLightness, false /*=red_to_violet*/);
    }
}
