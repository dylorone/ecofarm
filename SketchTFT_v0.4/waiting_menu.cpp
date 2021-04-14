#include "waiting_menu.h"

#include<TFT.h>
#include<Arduino.h>

#include "GUI_ID.h"
#include "gui_manager.h"
#include "climate_manager.h"
#include "image.h"
#include "encoder.h"

Text timeText(7, 15, 5, {125, 125, 125});
Text tempText(35, 88, 3, {2, 125, 0});

void WM_Show(TFT screen){
  GM_Show_Text(screen, &timeText, "NN:NN");

  screen.stroke(140, 140, 140);

  screen.line(10, 65, 150, 65);
  screen.line(10, 66, 150, 66);

  GM_Show_Text(screen, &tempText, "N/A");
  display_temperature_icon(115, 86, screen);
}

void WM_Update(TFT screen){
   GM_Update_Text(screen, &timeText, CM_Get_Time());
   GM_Update_Text(screen, &tempText, CM_Get_Temperature());
}

void WM_Handle_Event(TFT screen, unsigned char event){
  if(event == ROTATE_RIGHT) GM_Show_Menu(screen, WAITING_MENU_2);
}
