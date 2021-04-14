#include "cmt_cfg_menu.h"

#include<TFT.h>

#include "gui_manager.h"
#include "image.h"

Text dirtHumidity(20, (128 - 21) / 2, 3, {0, 127, 127});
Text airHumidity(160-GM_Count_TextSizeX(3, 3)-20, (128 - 21) / 2, 3, {0, 127, 127});

Button dirtHumBtn(0, CM_Hover_DirtBtn, CM_Click_DirtBtn, CM_Unhover_DirtBtn);
Button airHumBtn(1, CM_Hover_AirBtn, CM_Click_AirBtn, CM_Unhover_AirBtn);

void CM_Show(TFT* screen) {
  GM_Show_Text(screen, &dirtHumidity, "N/A");
  GM_Show_Text(screen, &airHumidity, "N/A");

  display_dirt_humidity_icon(20 + (GM_Count_TextSizeX(3, 3) / 2 - 12), (128 - 21) / 2 - 34, screen);
  display_air_humidity_icon(160 - (20 + GM_Count_TextSizeX(3, 3) / 2 + 12), (128 - 21) / 2 - 34, screen);

  GM_Alloc_Btns_Array(2);
  GM_Register_Button(screen, &dirtHumBtn);
  GM_Register_Button(screen, &airHumBtn);
}

void CM_Update(TFT* screen) {
  GM_Update_Text(screen, &dirtHumidity, "200");
  GM_Update_Text(screen, &airHumidity, "200");
}

void CM_Handle_Event(TFT* screen, unsigned char event, bool btn) {

}

void CM_Hover_DirtBtn(TFT* screen, Button* btn) {
  dirtHumidity.color = {127, 127, 0};
  GM_Show_Text(screen, &dirtHumidity, dirtHumidity.displayed_text);
}

void CM_Click_DirtBtn(TFT* screen, Button* btn) {

}

void CM_Unhover_DirtBtn(TFT* screen, Button* btn) {
  dirtHumidity.color = {0, 127, 127};
  GM_Show_Text(screen, &dirtHumidity, dirtHumidity.displayed_text);
}

void CM_Hover_AirBtn(TFT* screen, Button* btn) {
  airHumidity.color = {127, 127, 0};
  GM_Show_Text(screen, &airHumidity, airHumidity.displayed_text);
}

void CM_Click_AirBtn(TFT* screen, Button* btn) {

}

void CM_Unhover_AirBtn(TFT* screen, Button* btn) {
  airHumidity.color = {0, 127, 127};
  GM_Show_Text(screen, &airHumidity, airHumidity.displayed_text);
}
