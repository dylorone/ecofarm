#ifndef waiting_menu_h
#define waiting_menu_h

#include<TFT.h>

void WM_Show(TFT screen);
void WM_Update(TFT screen);
void WM_Handle_Event(TFT screen, unsigned char event);

#endif
