#include "gui_manager.h"

#include <TFT.h>
#include <Arduino.h>
//#include "waiting_menu.h"
//#include "waiting_menu_1.h"
#include "GUI_ID.h"

Text::Text(uint8_t posX, uint8_t posY, uint8_t fontSize, ColorRGB color){
  this->posX = posX;
  this->posY = posY;
  this->fontSize = fontSize;
  this->color = color;
  this->sizeX = 0;
  this->sizeY = 0;
  this->displayed_text = "";
};

void GM_Init(TFT screen){
  screen.background(0, 0, 0);
}

void GM_Show_Menu(TFT screen, Menu_ID m){
  screen.background(0, 0, 0);
  currentMenu = m;
  menus[m].show_menu(screen);
}

void GM_Register_Menu(Menu_ID m, void (*show_menu)(TFT screen), void (*update_menu)(TFT screen), void (*handle_event)(TFT screen, unsigned char event)){
  menus[m] = {m, show_menu, update_menu, handle_event};
}

void GM_Update_Menu(TFT screen){
  menus[currentMenu].update_menu(screen);
}

void GM_Call_Event(TFT screen, unsigned char e){
  menus[currentMenu].handle_event(screen, e);
}

void GM_Show_Text(TFT screen, Text* text, String newString){
  unsigned char textLength = newString.length()+1;
  
  char charText[textLength];
  newString.toCharArray(charText, textLength);

  text->displayed_text = newString;
  
  text->sizeX = (textLength-1)*5*text->fontSize + (textLength-2)*text->fontSize;
  text->sizeY = 7*text->fontSize;

  screen.fill(text->color.blue, text->color.green, text->color.red);
  screen.stroke(text->color.blue, text->color.green, text->color.red);
  screen.setTextSize(text->fontSize);
  
  screen.text(charText, text->posX, text->posY);
}

void GM_Update_Text(TFT screen, Text* text, String newString){
  if(newString == text->displayed_text || newString == "") return;
  
  screen.stroke(0, 0, 0);
  screen.fill(0, 0, 0);
  screen.rect(text->posX, text->posY, text->sizeX, text->sizeY);

  text->displayed_text = newString;
  unsigned char textLength = newString.length();

  char charText[textLength+1];
  newString.toCharArray(charText, textLength+1);
  
  text->sizeX = textLength*5*text->fontSize + (textLength-1)*text->fontSize;
  text->sizeY = 7*text->fontSize;
  
  screen.fill(text->color.blue, text->color.green, text->color.red);
  screen.stroke(text->color.blue, text->color.green, text->color.red);
  screen.setTextSize(text->fontSize);
  
  screen.text(charText, text->posX, text->posY);
}
