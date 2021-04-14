#include "led_effects.h"

#include "climate_manager.h"

#include <FastLED.h>
#include <math.h>

CRGB colors[4] = {CRGB::White, CRGB::Green, CRGB::Red, CRGB::Purple};

CRGB GradColor1 = CRGB(10, 10, 10);
unsigned char CurrentGradColor2 = 0;

CRGB SnakesBackg = CRGB::Purple;
CRGB SnakesGradColor = CRGB::Green;

unsigned int LE_Snakes(CRGB* leds, unsigned char occ){
  leds[occ] = CHSV(255/(NUM_LEDS/4)*occ, 255, 200);
  leds[45-occ] = CHSV(255/(NUM_LEDS/4)*occ, 255, 200);
  
  leds[22-occ] = CHSV(255/(NUM_LEDS/4)*occ, 255, 200);
  leds[23+occ] = CHSV(255/(NUM_LEDS/4)*occ, 255, 200);
  FastLED.show();

  return 100;
}

unsigned int LE_Gradient(CRGB* leds, unsigned char occ){
  if(occ == 0 && CurrentGradColor2 < 5){
    CurrentGradColor2++;
      if(CurrentGradColor2 == 4) CM_Toggle_FogAndPump();
      else if(CurrentGradColor2 == 5){
        CurrentGradColor2 = 0;
        CM_Show_LedEffect(LE_Snakes, NUM_LEDS/4);
        return 1000;
      }
  }
  
  float rDiff = getDiff(GradColor1.red, colors[CurrentGradColor2-1].red);
  float gDiff = getDiff(GradColor1.green, colors[CurrentGradColor2-1].green);
  float bDiff = getDiff(GradColor1.blue, colors[CurrentGradColor2-1].blue);

  float red = rDiff/250*occ;
  float green = gDiff/250*occ;
  float blue = bDiff/250*occ;
  
  for(int i=0;i<NUM_LEDS;i++){
    leds[i] = CRGB(GradColor1.red+round(red), GradColor1.green+round(green), GradColor1.blue+round(blue));
  }
  
  FastLED.show();
  
  return 20;
}

unsigned int LE_SnakeGradient(CRGB* leds, unsigned char occ){
  for(int i=0;i<NUM_LEDS;i++) leds[i] = SnakesBackg;
  
  float rDiff = getDiff(SnakesBackg.red, SnakesGradColor.red);
  float gDiff = getDiff(SnakesBackg.green, SnakesGradColor.green);
  float bDiff = getDiff(SnakesBackg.blue, SnakesGradColor.blue);

  float red = rDiff/5;
  float green = gDiff/5;
  float blue = bDiff/5;

  Serial.print("Red = ");
  Serial.print(red);
  Serial.print(" | Green = ");
  Serial.print(green);
  Serial.print(" | Blue = ");
  Serial.println(blue);

  for(int a=0;a<5;a++){
    leds[occ+a] = CRGB(SnakesBackg.red+round(red*a), SnakesBackg.green+round(green*a), SnakesBackg.blue+round(blue*a));
  }

  FastLED.show();
}

float getDiff(uint8_t a, uint8_t b){
  return b - a;
  
}
