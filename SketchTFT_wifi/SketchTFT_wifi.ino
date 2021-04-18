#include<iarduino_RTC.h>
#include<TFT.h>
#include<DHT.h>
#include<FastLED.h>

//Libraries
#include "RTOSlib.h"
#include "encoder.h"

//ID Configs
#include "pins.h"
#include "TASK_ID.h"
#include "GUI_ID.h"

//GUI
#include "image.h"
#include "gui_manager.h"

//Menu
#include "waiting_menu.h"
#include "waiting_menu_1.h"

//Special
#include "climate_manager.h"
#include "led_effects.h"
#include "wifi_mgt.h"


TFT screen(CS_PIN, DC_PIN, SCRST_PIN);
Encoder enc(ENC_LEFT, ENC_RIGHT, true, ENC_BTN);

void execute_enc_handler(int tid){
  unsigned char result = enc.tick();
  enc.tickButton();
  GM_Call_Event(screen, result);
}

void execute_gui_handler(int tid){
  GM_Update_Menu(screen);
}

void execute_climate_handler(int tid){
  CM_Loop();
}

void registerAllTasks(){
  registerTask(ENCODER_HANDLER, 5, execute_enc_handler);
  registerTask(CLIMATE_HANDLER, 100, execute_climate_handler);
  registerTask(GUI_UPDATER, 500, execute_gui_handler);
  registerTask(FOG_DEMO, 1000, CM_Fog);
  registerTask(LED_EFFECTS, 5000, CM_Update_Leds);
  registerTask(PUMP_DEMO, 1000, CM_Pump);
  registerTask(WIFI_MGT, 500, WIFI_Loop);
}

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  
  pinMode(ENC_LEFT, INPUT);
  pinMode(ENC_RIGHT, INPUT);
  pinMode(ENC_BTN, INPUT_PULLUP);
  
  pinMode(FAN_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(FOG_PIN, OUTPUT);
  pinMode(DHT_PIN, OUTPUT);

  pinMode(SEN_ENABLE_PIN, OUTPUT);
  
  screen.begin();
  screen.setRotation(3);
  
  CM_Init();
  GM_Init(screen);
  WIFI_Init();

  GM_Register_Menu(WAITING_MENU_1, WM_Show, WM_Update, WM_Handle_Event);
  GM_Register_Menu(WAITING_MENU_2, WM1_Show, WM1_Update, WM1_Handle_Event);
  //GM_Register_Menu(WAITING_MENU_3, WM2_Show, WM2_Update, WM2_Handle_Event);
  
  registerAllTasks();
  
  GM_Show_Menu(screen, WAITING_MENU_1);
  
  CM_Show_LedEffect(LE_Gradient, 250);
  //CM_Toggle_LedEffects();

  randomSeed(analogRead(0));
}

void loop() {
  checkTasks();
}
