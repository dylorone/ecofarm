#ifndef cmt_cfg_menu_h
#define cmt_cfg_menu_h

#include<TFT.h>
#include "gui_manager.h"

void CM_Show(TFT* screen);
void CM_Update(TFT* screen);
void CM_Handle_Event(TFT* screen, unsigned char event, bool btn);

void CM_Hover_DirtBtn(TFT* screen, Button* btn);
void CM_Click_DirtBtn(TFT* screen, Button* btn);
void CM_Unhover_DirtBtn(TFT* screen, Button* btn);


void CM_Hover_AirBtn(TFT* screen, Button* btn);
void CM_Click_AirBtn(TFT* screen, Button* btn);

void CM_Unhover_AirBtn(TFT* screen, Button* btn);

#endif
