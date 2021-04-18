#include "image.h"
#include <TFT.h>
#include <Arduino.h>

void display_humidity_icon(unsigned char x, unsigned char y, TFT screen){
  screen.stroke(humidity_icon_color[2], humidity_icon_color[1], humidity_icon_color[0]);

  for(uint8_t col=0;col<HUMIDITY_ICON_WIDTH;col++){
    for(uint8_t row=0;row<HUMIDITY_ICON_HIGHT;row++){
      for(uint8_t bitrow=0;bitrow<8;bitrow++){
        uint8_t bit_check = (128>>bitrow)&pgm_read_word(&humidity_icon[row][col]);
        if(bit_check != 0){
          screen.rect(x+(col*8+bitrow), y+row, 1, 1);
        }
      }
    }
  }
}

void display_temperature_icon(unsigned char x, unsigned char y, TFT screen){
  screen.stroke(temperature_icon_color[2], temperature_icon_color[1], temperature_icon_color[0]);

  for(uint8_t col=0;col<TEMP_ICON_WIDTH;col++){
    for(uint8_t row=0;row<TEMP_ICON_HIGHT;row++){
      for(uint8_t bitrow=0;bitrow<8;bitrow++){
        uint8_t bit_check = (128>>bitrow)&pgm_read_word(&temperature_icon[row][col]);
        if(bit_check != 0){
          screen.rect(x+(col*8+bitrow), y+row, 1, 1);
        }
      }
    }
  }
}

void display_wifi_icon(unsigned char x, unsigned char y, TFT screen){
  screen.stroke(wifi_icon_color[2], wifi_icon_color[1], wifi_icon_color[0]);

  for(uint8_t col=0;col<WIFI_ICON_WIDTH;col++){
    for(uint8_t row=0;row<WIFI_ICON_HIGHT;row++){
      for(uint8_t bitrow=0;bitrow<8;bitrow++){
        uint8_t bit_check = (128>>bitrow)&pgm_read_word(&wifi_icon[row][col]);
        if(bit_check != 0){
          screen.rect(x+(col*8+bitrow), y+row, 1, 1);
        }
      }
    }
  }
}

void display_air_humidity_icon(unsigned char x, unsigned char y, TFT screen){
  screen.stroke(air_humidity_icon_color[2], air_humidity_icon_color[1], air_humidity_icon_color[0]);

  for(uint8_t col=0;col<AIR_HUMIDITY_WIDTH;col++){
    for(uint8_t row=0;row<AIR_HUMIDITY_HIGHT;row++){
      for(uint8_t bitrow=0;bitrow<8;bitrow++){
        uint8_t bit_check = (128>>bitrow)&pgm_read_word(&air_humidity_icon[row][col]);
        if(bit_check != 0){
          screen.rect(x+(col*8+bitrow), y+row, 1, 1);
        }
      }
    }
  }
}


void display_dirt_humidity_icon(unsigned char x, unsigned char y, TFT screen){
  screen.stroke(dirt_humidity_icon_color[2], dirt_humidity_icon_color[1], dirt_humidity_icon_color[0]);

  for(uint8_t col=0;col<DIRT_HUMIDITY_WIDTH;col++){
    for(uint8_t row=0;row<DIRT_HUMIDITY_HIGHT;row++){
      for(uint8_t bitrow=0;bitrow<8;bitrow++){
        uint8_t bit_check = (128>>bitrow)&pgm_read_word(&dirt_humidity_icon[row][col]);
        if(bit_check != 0){
          screen.rect(x+(col*8+bitrow), y+row, 1, 1);
        }
      }
    }
  }
}
