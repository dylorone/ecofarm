#include "gui_manager.h"

#include <TFT.h>
#include <Arduino.h>

#include "Encoder.h"
#include "GUI_ID.h"

//Конструктор текста
Text::Text(uint8_t posX, uint8_t posY, uint8_t fontSize, ColorRGB color){
  this->posX = posX;
  this->posY = posY;
  this->fontSize = fontSize;
  this->color = color;
  this->sizeX = 0;
  this->sizeY = 0;
  this->displayed_text = "";
};

//Конструктор кнопки
Button::Button(unsigned char id, void (*hover)(TFT* screen, Button *btn), void (*clk)(TFT* screen, Button *btn), void (*unhover)(TFT* screen, Button *btn)){
  this->id = id;
  this->hover = hover;
  this->clk = clk;
  this->unhover = unhover;
}

//Инициализация
void GM_Init(TFT* screen){
  screen->background(0, 0, 0);                            //Сброс экрана
}

//Показ меню
void GM_Show_Menu(TFT* screen, Menu_ID m){
  screen->background(0, 0, 0);                            //Сброс экрана
  currentMenu = m;                                        //Текущее меню = меню, которое нужно открыть
  
  if(buttonsArrSize != 0){                                //Еслив прошлом меню кнопки были
    free(btns);                                           //Удаление массива
    buttonsArrSize = 0;                                   //Сброс размера массива
  }
  
  menus[m].show_menu(screen);                             //Вызов функции показа меню
}

//Ренгистрация меню
void GM_Register_Menu(Menu_ID m, void (*show_menu)(TFT* screen), void (*update_menu)(TFT* screen), void (*handle_event)(TFT* screen, unsigned char event, bool btn)){
  menus[m] = {m, show_menu, update_menu, handle_event};
}

//Обновление меню
void GM_Update_Menu(TFT* screen){
  menus[currentMenu].update_menu(screen);
}

//Управление событиями (нажатие кнопки и т.д.)
void GM_Call_Event(TFT* screen, unsigned char e, bool btn){
  Menu_ID cMenu = currentMenu;
  
  if(e == ROTATE_RIGHT && buttonsArrSize > 0){
    btns[selectedButton].unhover(screen, &btns[selectedButton]);
    selectedButton++;
    if(buttonsArrSize == selectedButton) selectedButton = 0;
    btns[selectedButton].hover(screen, &btns[selectedButton]);
  }

  else if(e == ROTATE_LEFT && buttonsArrSize > 0){
    btns[selectedButton].unhover(screen, &btns[selectedButton]);
    selectedButton--;
    if(selectedButton > buttonsArrSize) selectedButton = buttonsArrSize - 1;
    btns[selectedButton].hover(screen, &btns[selectedButton]);
 }

  if(btn == true && buttonsArrSize > 0) btns[selectedButton].clk(screen, &btns[selectedButton]);

  if(cMenu != currentMenu) return;
  menus[currentMenu].handle_event(screen, e, btn);
}

//Создание массива кнопок
void GM_Alloc_Btns_Array(unsigned char len){
  btns = calloc(len, sizeof(struct Button));
  buttonsArrSize = len;
}

//Регистрация кнопки
void GM_Register_Button(TFT* screen, Button* btn){
  if(btn->id >= buttonsArrSize) return;

  btns[btn->id] = *btn;
  
  if(btn->id == 0){
    btn->hover(screen, btn);
    selectedButton = btn->id;
  }
}

//Показ текста
void GM_Show_Text(TFT* screen, Text* text, String newString){
  unsigned char textLength = newString.length()+1;
  
  char charText[textLength];
  newString.toCharArray(charText, textLength);

  text->displayed_text = newString;
  
  text->sizeX = (textLength-1)*5*text->fontSize + (textLength-2)*text->fontSize;
  text->sizeY = 7*text->fontSize;

  screen->fill(text->color.blue, text->color.green, text->color.red);
  screen->stroke(text->color.blue, text->color.green, text->color.red);
  screen->setTextSize(text->fontSize);
  
  screen->text(charText, text->posX, text->posY);
}

//Обновление текста
void GM_Update_Text(TFT* screen, Text* text, String newString){
  if(newString == text->displayed_text || newString == "") return;
  
  screen->stroke(0, 0, 0);
  screen->fill(0, 0, 0);
  screen->rect(text->posX, text->posY, text->sizeX, text->sizeY);

  text->displayed_text = newString;
  unsigned char textLength = newString.length();

  char charText[textLength+1];
  newString.toCharArray(charText, textLength+1);
  
  text->sizeX = textLength*5*text->fontSize + (textLength-1)*text->fontSize;
  text->sizeY = 7*text->fontSize;
  
  screen->fill(text->color.blue, text->color.green, text->color.red);
  screen->stroke(text->color.blue, text->color.green, text->color.red);
  screen->setTextSize(text->fontSize);
  
  screen->text(charText, text->posX, text->posY);
}

//Сброс текста
void GM_Clear_Text(TFT* screen, Text* text, ColorRGB color){
  screen->stroke(color.blue, color.green, color.red);
  screen->fill(color.blue, color.green, color.red);
  screen->rect(text->posX, text->posY, text->sizeX, text->sizeY);
}

unsigned char GM_Count_TextSizeX(unsigned char len, unsigned char fontSize){
  return len*5*fontSize + (len-1)*fontSize;
}

unsigned char GM_Count_TextSizeY(unsigned char len, unsigned char fontSize){
  return 7*fontSize;
}
