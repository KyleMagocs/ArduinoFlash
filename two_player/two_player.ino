#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define P1_PIXEL  12
#define P1_INTERVAL  3
#define P2_PIXEL  7
#define P2_INTERVAL  2

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(P1_PIXEL + P2_PIXEL, PIN, NEO_GRB + NEO_KHZ800);

int all_colors[][3] = {
  {0, 255, 0},
  {255, 0, 0},
  {51, 102, 153},
  {0, 255, 255},
  {0, 153, 51},
  {0, 102, 51},
  {153,153,51},
  {153,102,51},
  {102,0,102},
  {153,0,204},
  {255,0,255},
  {255,102,0},
  {255,255,0},
  {0, 0, 255}
};

int p1_colors[3] = {150, 150, 150};
int p2_colors[3] = {150, 150, 150};

int delayval = 200;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  //theaterChase(pixels.Color(0, 0, 127), 50); // Blue


  for (int i = 0; i < P1_INTERVAL * P2_INTERVAL; i++) {
    spin(0, P1_PIXEL, p1_colors[0], p1_colors[1], p1_colors[2], 3, i);
    spin(P1_PIXEL + 1, P1_PIXEL + P2_PIXEL, p2_colors[0], p2_colors[1], p2_colors[2], 3, i);
    pixels.show(); // This sends the updated pixel color to the hardware.

    if (Serial.available() > 0) {
      String str = Serial.readString();
      char foo[5];
      strcpy(foo, str.c_str());
      char *p = strtok(foo, "|");

      int index1 = atoi(p);
      int index2 = atoi(strtok(NULL, "|"));
      memcpy(p1_colors, all_colors[index1], 3 * sizeof(int));
      memcpy(p2_colors, all_colors[index2], 3 * sizeof(int));;
    }
    else {
      delay(delayval);
    }
    spin(0, P1_PIXEL, 0, 0, 0, 3, i);
    spin(P1_PIXEL + 1, P1_PIXEL + P2_PIXEL, 0, 0, 0, 3, i);
    pixels.show();
  }
}


void spin(int startpix, int endpix, int r, int g, int b, int interval, int offset) {
  for (int i = (startpix + offset) % interval + startpix; i < endpix; i += interval) {
    //    char foo[20];
    //    sprintf(foo, "Pix: %d", i);
    //    Serial.println(foo);
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
}


