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
const double kLedRefreshRate = 50;  // Hzt
const double kVerticalRotationRate = 0.5;  // Hzt

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
DMAMEM int display_memory[kLedsPerStrip*6];
int drawing_memory[kLedsPerStrip*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(kLedsPerStrip, display_memory, drawing_memory, config);

// Initialize color palette memory.
const int kColorsLength = kVerticalStripLen;
int Colors[kColorsLength];

const int kColorWidth = 15;
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

void setup() {
  // Put your setup code here, to run once:
  MakeColors();
  leds.begin();

}

void loop() {
  // Put your main code here, to run repeatedly:
  RotateVertical(kVerticalRotationRate, kLedRefreshRate, kLedsPerStrip, Colors, kColorsLength);
}
