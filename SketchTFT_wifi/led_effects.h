#ifndef led_effects_h
#define led_effects_h

#include<FastLED.h>

unsigned int LE_Snakes(CRGB* leds, unsigned char occ);
unsigned int LE_Gradient(CRGB* leds, unsigned char occ);
unsigned int LE_SnakeGradient(CRGB* leds, unsigned char occ);

float getDiff(uint8_t a, uint8_t b);

#endif
