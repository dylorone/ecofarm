#ifndef led_effects_h
#define led_effects_h

#include<FastLED.h>

unsigned long LE_Snakes(CRGB* leds, unsigned char occ);
unsigned long LE_Gradient(CRGB* leds, unsigned char occ);
unsigned long LE_SnakeGradient(CRGB* leds, unsigned char occ);

float getDiff(uint8_t a, uint8_t b);

#endif
