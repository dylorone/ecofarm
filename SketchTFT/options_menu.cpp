#include "options_menu.h"
#include "gui_manager.h"

#include<TFT.h>

#define NUMBER_OF_ENTRIES 4
#define FONT_SIZE 3
#define TEXT_HEIGHT FONT_SIZE*7

#define UP_DOWN_INDENT 15
#define BETWEEN_LINES_INDENT (int) (128 - UP_DOWN_INDENT*2 - TEXT_HEIGHT*NUMBER_OF_ENTRIES) / (NUMBER_OF_ENTRIES - 1)


Text climateText(28, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*0, FONT_SIZE, {0, 127, 10});
Text clockText(28, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*1, FONT_SIZE, {0, 127, 10});
Text wifiText(28, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*2, FONT_SIZE, {0, 127, 10});
Text quitText(28, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*3, FONT_SIZE, {0, 127, 10});

Button climateBtn(0, OM_Hover_ClimateButton, OM_Click_ClimateButton, OM_Unhover_ClimateButton);
Button clockBtn(1, OM_Hover_ClockButton, OM_Click_ClockButton, OM_Unhover_ClockButton);
Button wifiBtn(2, OM_Hover_WifiButton, OM_Hover_WifiButton, OM_Unhover_WifiButton);
Button quitBtn(3, OM_Hover_QuitButton, OM_Click_QuitButton, OM_Unhover_QuitButton);

void OM_Show(TFT* screen){
  GM_Show_Text(screen, &climateText, "Climate");
  GM_Show_Text(screen, &clockText, "Clock");
  GM_Show_Text(screen, &wifiText, "Wi-Fi");
  GM_Show_Text(screen, &quitText, "Quit");
  
  GM_Alloc_Btns_Array(NUMBER_OF_ENTRIES);
  GM_Register_Button(screen, &climateBtn);
  GM_Register_Button(screen, &clockBtn);
  GM_Register_Button(screen, &wifiBtn);
  GM_Register_Button(screen, &quitBtn);
}

void OM_Update(TFT* screen){
  
}

void OM_Handle_Event(TFT* screen, unsigned char event, bool btn){
  //if(btn == true) GM_Show_Menu(screen, WAITING_MENU_1);
}

//****************************CLIMATE BUTTON****************************
void OM_Hover_ClimateButton(TFT* screen, Button* btn){
  Serial.println("Climate hover!!!");

  screen->fill(255, 255, 255);
  screen->stroke(255, 255, 255);
  screen->rect(5, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*0, 16, 16);
}

void OM_Click_ClimateButton(TFT* screen, Button* btn){
  Serial.println("Climate click!!!");

  GM_Show_Menu(screen, CLIMATE_CFG_MENU);
}

void OM_Unhover_ClimateButton(TFT* screen, Button* btn){
  Serial.println("Climate unhover!");
  
  screen->fill(0, 0, 0);
  screen->stroke(0, 0, 0);
  screen->rect(5, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*0, 16, 16);
}

//***********************CLOCK BUTTON**************************************
void OM_Hover_ClockButton(TFT* screen, Button btn){
  screen->fill(255, 255, 255);
  screen->stroke(255, 255, 255);
  screen->rect(5, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*1, 16, 16);
}

void OM_Click_ClockButton(TFT* screen, Button btn){
  
}

void OM_Unhover_ClockButton(TFT* screen, Button btn){
  screen->fill(0, 0, 0);
  screen->stroke(0, 0, 0);
  screen->rect(5, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*1, 16, 16);
}

//*************************Wi-Fi BUTTON*********************************
void OM_Hover_WifiButton(TFT* screen, Button btn){
  screen->fill(255, 255, 255);
  screen->stroke(255, 255, 255);
  screen->rect(5, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*2, 16, 16);
}

void OM_Click_WifiButton(TFT* screen, Button btn){
  
}

void OM_Unhover_WifiButton(TFT* screen, Button btn){
  screen->fill(0, 0, 0);
  screen->stroke(0, 0, 0);
  screen->rect(5, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*2, 16, 16);
}

//***********************************************************************
void OM_Hover_QuitButton(TFT* screen, Button btn){
  screen->fill(255, 255, 255);
  screen->stroke(255, 255, 255);
  screen->rect(5, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*3, 16, 16);
}

void OM_Click_QuitButton(TFT* screen, Button btn){
  GM_Show_Menu(screen, WAITING_MENU_1);
}

void OM_Unhover_QuitButton(TFT* screen, Button btn){
  screen->fill(0, 0, 0);
  screen->stroke(0, 0, 0);
  screen->rect(5, UP_DOWN_INDENT+(TEXT_HEIGHT+BETWEEN_LINES_INDENT)*3, 16, 16);
}
