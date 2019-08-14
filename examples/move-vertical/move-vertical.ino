#include <OctoWS2811.h>

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF
#define BLACK  0x000000



const int ledsPerStrip = 412;
const int shortVertical = 40;
const int longVertical = 100;
const int ledsPerVertical = shortVertical + longVertical;
const int ColorLength = ledsPerVertical;
int Colors[ColorLength];
const int verticalStripCount = 6;
const int midStrip = verticalStripCount;
const int topStrip = verticalStripCount + 1;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

const int colorWidth = 15;

void MakeColors() {
  for (int index = 0; index < ColorLength; index++) {
    Colors[index] = BLACK;
  }
  for (int index = 0; index < colorWidth; index++) {
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

void MoveVertical(int wait_us) {
  int up_sample_rate = ledsPerStrip / ColorLength;
  for (int color = 0; color < ColorLength; color++) {
    // Set color for the vertical strips.
    for (int led_index = 0; led_index < ledsPerVertical; led_index++) {
      for (int led_strip = 0; led_strip < verticalStripCount; led_strip++) {
        const int color_index = (color + led_index / up_sample_rate) % ColorLength;
        leds.setPixel(led_index + led_strip*ledsPerStrip, Colors[color_index]);
      }
    }
    // Set color for the mid strip.
    for (int led_index = 0; led_index < ledsPerStrip; led_index++) {
      const int color_index = (color + shortVertical / up_sample_rate) % ColorLength;
      leds.setPixel(led_index + midStrip*ledsPerStrip, Colors[color_index]);
    }
    // Set color for the top strip.
    for (int led_index = 0; led_index < ledsPerStrip; led_index++) {
      const int color_index = (color + 0 / up_sample_rate) % ColorLength;
      leds.setPixel(led_index + topStrip*ledsPerStrip, Colors[color_index]);
    }
    leds.show();
    delayMicroseconds(wait_us);
  }
}

void setup() {
  // put your setup code here, to run once:
  MakeColors();
  leds.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  MoveVertical(40000);
}
