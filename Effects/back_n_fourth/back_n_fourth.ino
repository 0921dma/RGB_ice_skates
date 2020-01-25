#include "FastLED.h"
#define NUM_LEDS 5
CRGB leds[NUM_LEDS];
#define PIN 6

void setup()
{
  FastLED.addLeds< WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
}






void loop() {
  back_n_fourth (0xff, 0xff, 0xff, 100, 0);
  back_n_fourth (0xff, 0x00, 0x00, 100, 1);
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
