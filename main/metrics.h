// This file defines a few parameters including animation variables and
// dwelling architectural dimentions.

#ifndef MAIN_METRICS_H_
#define MAIN_METRICS_H_

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define PINK 0xFF1088
#define ORANGE 0xE05800
#define WHITE 0xFFFFFF
#define BLACK 0x000000

// Animation configs.
const double kLedRefreshFreq = 50;        // Hz
const double kVerticalRotationFreq = 0.5; // Hz
const double kPolarRotationFreq = 1.0;    // Hz
const double kRainbowLightnessFreq = 0.5; // Hz
const double kRainbowHueFreq = 0.01;      // Hz

// Palette configs.
const unsigned int kMaxHue = 360;
const unsigned int kSaturation = 100;
const double kMidLightness = 50.0;
const double kLowLightness = 25.0;
const double kHighLightness = 75.0;

// Dwelling measurements and architecture.
#define kTopStripLen 50
#define kMidStripLen 412
#define kAugMidStripLen (kMidStripLen + kMidStripLen / 5)
#define kUpperVerticalStripLen 40
#define kLowerVerticalStripLen 100
#define kVerticalStripLen (kUpperVerticalStripLen + kLowerVerticalStripLen)
#define kLedsPerStrip kAugMidStripLen

#define kVerticalStripCount 6
#define kMidStripIndex kVerticalStripCount
#define kTopStripIndex (kVerticalStripCount + 1)
#define NUM_LEDS (kLedsPerStrip * 6)

const double kUpperHeightRatio = 0.1;
const double kStripPolarPositions[6] = {0, 1 / 6, 2 / 6, 3 / 6, 4 / 6, 5 / 6};

#endif
