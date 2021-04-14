#ifndef gui_manager_h
#define gui_manager_h

#include<Arduino.h>
#include<TFT.h>

#include "GUI_ID.h"

#define MENUS_REGISTERED 2

typedef struct Menu {
  Menu_ID id;
  void (*show_menu)(TFT screen);
  void (*update_menu)(TFT screen);
  void (*handle_event)(TFT screen, unsigned char event);
};

typedef struct ColorRGB {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

class Text {
  public:
  String displayed_text;
  uint8_t posX;
  uint8_t posY;
  uint8_t sizeX;
  uint8_t sizeY;
  uint8_t fontSize;
  ColorRGB color;

  Text(uint8_t posX, uint8_t posY, uint8_t fontSize, ColorRGB color);
};

static Menu menus[MENUS_REGISTERED];
static Menu_ID currentMenu;

void GM_Init(TFT screen);
void GM_Show_Menu(TFT screen, Menu_ID m);
void GM_Update_Menu(TFT screen);
void GM_Register_Menu(Menu_ID m, void (*show_menu)(TFT screen), void (*update_menu)(TFT screen), void (*handle_event)(TFT screen, unsigned char event));
void GM_Call_Event(TFT screen, unsigned char e);
void GM_Show_Text(TFT screen, Text* text, String newString);
void GM_Update_Text(TFT screen, Text* text, String newString);

#endif
