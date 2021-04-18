#include "waiting_menu_1.h"

#include<TFT.h>

#include "waiting_menu.h"
#include "GUI_ID.h"
#include "encoder.h"
#include "gui_manager.h"
#include "climate_manager.h"
#include "image.h"

Text airHumText(20, 22, 4, {19, 214, 214});
Text dirtHumText(70, 82, 4, {230, 169, 0});

void WM1_Show(TFT screen){
  GM_Show_Text(screen, &airHumText, "N/A");
  display_air_humidity_icon(123, 10, screen);
  
  screen.stroke(140, 140, 140);
  
  screen.line(10, 65, 150, 65);
  screen.line(10, 66, 150, 66);

  display_dirt_humidity_icon(25, 87, screen);
  GM_Show_Text(screen, &dirtHumText, "N/A");
}

void WM1_Update(TFT screen){
  GM_Update_Text(screen, &airHumText, CM_Get_AirHumidity());
  GM_Update_Text(screen, &dirtHumText, CM_Get_DirtHumidity());
}

void WM1_Handle_Event(TFT screen, unsigned char event){
  if(event == ROTATE_LEFT) GM_Show_Menu(screen, WAITING_MENU_1);
}
