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
const double kPolarRotationFreq = 0.5;  // Hz
const double kRainbowLightnessFreq = 0.5;  // Hz
const double kRainbowHueFreq = 0.01;  // Hz

// Palette configs.
const unsigned int kMaxHue = 360;
const unsigned int kSaturation = 100;
const double kMidLightness = 50.0;
const double kLowLightness = 25.0;
const double kHighLightness = 75.0;



// Dwelling measurements and architecture.
const int kTopStripLen = 254;
const int kTopStripOffset = 106;
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
const double kStripPolarPositions[6] = {1.0/6, 0/6, 5.0/6, 4.0/6, 3.0/6, 2.0/6};

#endif
