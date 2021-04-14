#ifndef gui_manager_h
#define gui_manager_h

#include<Arduino.h>
#include<TFT.h>

#include "GUI_ID.h"

#define MENUS_REGISTERED 4

typedef struct Menu {
  Menu_ID id;
  void (*show_menu)(TFT* screen);
  void (*update_menu)(TFT* screen);
  void (*handle_event)(TFT* screen, unsigned char event, bool btn);
};

typedef struct ColorRGB {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

typedef struct Button{
  void (*hover)(TFT* screen, Button *btn);
  void (*clk)(TFT* screen, Button *btn);
  void (*unhover)(TFT* screen, Button *btn);
  unsigned char id;
  bool hovered;

  Button(unsigned char id, void (*hover)(TFT* screen, Button *btn), void (*clk)(TFT* screen, Button *btn), void (*unhover)(TFT* screen, Button *btn));
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

static Button *btns;
static unsigned char selectedButton;
static unsigned char buttonsArrSize;

void GM_Init(TFT* screen);
void GM_Show_Menu(TFT* screen, Menu_ID m);
void GM_Update_Menu(TFT* screen);
void GM_Alloc_Btns_Array(unsigned char len);
void GM_Register_Button(TFT* screen, Button* btn);
void GM_Register_Menu(Menu_ID m, void (*show_menu)(TFT* screen), void (*update_menu)(TFT* screen), void (*handle_event)(TFT* screen, unsigned char event, bool btn));
void GM_Call_Event(TFT* screen, unsigned char e, bool btn);
void GM_Show_Text(TFT* screen, Text* text, String newString);
void GM_Update_Text(TFT* screen, Text* text, String newString);
unsigned char GM_Count_TextSizeX(unsigned char len, unsigned char fontSize);
unsigned char GM_Count_TextSizeY(unsigned char len, unsigned char fontSize);

#endif
