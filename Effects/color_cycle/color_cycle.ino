#include "FastLED.h"
#define NUM_LEDS 5
CRGB leds[NUM_LEDS];
#define PIN 6

void setup()
{
  FastLED.addLeds< WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
}






void loop() {
  color_cycle (0);
}

void color_cycle (int wait_time) {
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
