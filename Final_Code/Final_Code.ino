#include "FastLED.h"
#define NUM_LEDS 5
CRGB leds[NUM_LEDS];
#define PIN 6
int mode = 0;

void setup()
{
  FastLED.addLeds< WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    int data = Serial.read() - '0';
    if (data > 0) mode = data;
  }

  if (mode == 0) // //  ***Static Color when turned on***    OK
  {
    setAll(0x00, 0x00, 0xff);  //just the color
  }
  else if (mode == 1) // ***Color Wipe***     OK
  {
    colorWipe (0x00, 0xff, 0x00, 50);   // color
    colorWipe (0x00, 0x00, 0x00, 50);   //  leds off (second color)
  }
  else if (mode == 2) //  ***Fade***     OK
  {
    FadeInOut(0xff, 0xff, 0xff); // red
    FadeInOut(0x00, 0xff, 0x00); // white
  }
  else if (mode == 3) // ***Sparkle***     OK
  {
    Sparkle(0xff, 0x00, 0x00, 200);   //  color_sparkle/color_background/Speed
  }
  else if (mode == 4) // ***Rainbow***    OK
  {
    rainbow(0);  //  Speed
  }
  else if (mode == 5) // ***color_cycle***   OK
  {
    color_cycle (0);  //  Speed
  }
  /*else if (mode == 6) // ***back_n_fourth***  NOT OK
  {
    back_n_fourth (0xff, 0xff, 0xff, 100, 0);
    back_n_fourth (0xff, 0x00, 0x00, 100, 1);
  }*/
}

//Effects

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {   // ***Color Wipe***
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    setPixel(i, red, green, blue);
    showStrip();
    delay(SpeedDelay);
  }
}


void FadeInOut(byte red, byte green, byte blue) {  //  ***Fade***
  float r, g, b;

  for (int k = 0; k < 256; k = k + 1) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
  }

  for (int k = 255; k >= 0; k = k - 2) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
    showStrip();
  }
}


void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {   //  ***Sparkle***
  setAll(red, green, blue);
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel, 0xff, 0xff, 0xff);
  showStrip();
  delay(SpeedDelay);
}



void rainbow(int SpeedDelay) {   //  ***Rainbow***
  byte *c;
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < NUM_LEDS; i++) {
      c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c + 1), *(c + 2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}



void color_cycle (int wait_time) {   //  ***color_cycle***
  for (int colorStep = 0; colorStep <= 255; colorStep++) {
    int r = 255;
    int g = 0;
    int b = colorStep;
    // Now loop though each of the LEDs and set each one to the current color
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[x] = CRGB(r, g, b);
    }
    // Display the colors we just set on the actual LEDs
    delay(wait_time);
    LEDS.show();
  }

  //into blue
  for (int colorStep = 255; colorStep >= 0; colorStep--) {
    int r = colorStep;
    int g = 0;
    int b = 255;
    // Now loop though each of the LEDs and set each one to the current color
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[x] = CRGB(r, g, b);
    }
    // Display the colors we just set on the actual LEDs
    delay(wait_time);
    LEDS.show();
  }
  //start from blue
  for (int colorStep = 0; colorStep <= 255; colorStep++) {
    int r = 0;
    int g = colorStep;
    int b = 255;
    // Now loop though each of the LEDs and set each one to the current color
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[x] = CRGB(r, g, b);
    }
    // Display the colors we just set on the actual LEDs
    delay(wait_time);
    LEDS.show();
  }
  //into green
  for (int colorStep = 255; colorStep >= 0; colorStep--) {
    int r = 0;
    int g = 255;
    int b = colorStep;
    // Now loop though each of the LEDs and set each one to the current color
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[x] = CRGB(r, g, b);
    }
    // Display the colors we just set on the actual LEDs
    delay(wait_time);
    LEDS.show();
  }
  //start from green
  for (int colorStep = 0; colorStep <= 255; colorStep++) {
    int r = colorStep;
    int g = 255;
    int b = 0;
    // Now loop though each of the LEDs and set each one to the current color
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[x] = CRGB(r, g, b);
    }
    // Display the colors we just set on the actual LEDs
    delay(wait_time);
    LEDS.show();
  }
  //into yellow
  for (int colorStep = 255; colorStep >= 0; colorStep--) {
    int r = 255;
    int g = colorStep;
    int b = 0;
    // Now loop though each of the LEDs and set each one to the current color
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[x] = CRGB(r, g, b);
    }
    // Display the colors we just set on the actual LEDs
    delay(wait_time);
    LEDS.show();
  }
}



void back_n_fourth (byte red, byte green, byte blue, int Delay, int Direction) {
  if (Direction == 0)
  {
    for (int i = 0; i <= NUM_LEDS; i++)
    {
      setPixel(i, red, green, blue);
      showStrip();
      delay(Delay);
    }
  }
  else if (Direction == 1)
  {
    for (int i = 5; i >= 0; i--)
    {
      setPixel(i, red, green, blue);
      showStrip();
      delay(Delay);
    }
  }
}


void showStrip() {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.show();
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  FastLED.show();
#endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
#endif
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}
