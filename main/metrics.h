// This file defines a few parameters including animation variables and
// dwelling architectural dimentions.

#ifndef MAIN_METRICS_H_
#define MAIN_METRICS_H_

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
const double kPolarRotationFreq = 1.0;  // Hz
const double kRainbowLightnessFreq = 0.5;  // Hz
const double kRainbowHueFreq = 0.01;  // Hz
const double kRainbowMinLightness = 5;  // Lower bound is 0
const double kRainbowMaxLightness = 40;  // Upper bound is 50

// Dwelling measurements and architecture.
const int kTopStripLen = 50;
const int kMidStripLen = 412;
const int kAugMidStripLen = kMidStripLen + kMidStripLen / 5;
const int kUpperVerticalStripLen = 40;
const int kLowerVerticalStripLen = 100;
const int kVerticalStripLen = kUpperVerticalStripLen + kLowerVerticalStripLen;
const int kLedsPerStrip = kAugMidStripLen;

const int kVerticalStripCount = 6;
const int kMidStripIndex = kVerticalStripCount;
const int kTopStripIndex = kVerticalStripCount + 1;

const double kUpperHeightRatio = 0.1;
const double kStripPolarPositions[6] = {0, 1/6, 2/6, 3/6, 4/6, 5/6};

#endif
