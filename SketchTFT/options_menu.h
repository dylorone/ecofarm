#ifndef options_menu_h
#define options_menu_h

#include <TFT.h>
#include "gui_manager.h"

void OM_Show(TFT* screen);
void OM_Update(TFT* screen);
void OM_Handle_Event(TFT* screen, unsigned char event, bool btn);

void OM_Hover_ClimateButton(TFT* screen, Button* btn);
void OM_Click_ClimateButton(TFT* screen, Button* btn);
void OM_Unhover_ClimateButton(TFT* screen, Button* btn);

void OM_Hover_ClockButton(TFT* screen, Button btn);
void OM_Click_ClockButton(TFT* screen, Button btn);
void OM_Unhover_ClockButton(TFT* screen, Button btn);
 
void OM_Hover_WifiButton(TFT* screen, Button btn);
void OM_Click_WifiButton(TFT* screen, Button btn);
void OM_Unhover_WifiButton(TFT* screen, Button btn);

void OM_Hover_QuitButton(TFT* screen, Button btn);
void OM_Click_QuitButton(TFT* screen, Button btn);
void OM_Unhover_QuitButton(TFT* screen, Button btn);

#endif
