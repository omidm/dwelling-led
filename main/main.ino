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

void setup() {
  // Put your setup code here, to run once:
  MakeColors();
  leds.begin();

}

void loop() {
  // Put your main code here, to run repeatedly:
  RotateVertical(.5, kLedRefreshRate, Colors, kColorsLength);
}
