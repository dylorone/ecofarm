#include<iarduino_RTC.h>
#include<TFT.h>
#include<DHT.h>
#include<FastLED.h>

//Libraries
#include "RTOSlib.h"                            //Библиотека RTOS
#include "encoder.h"                            //Библиотека для работы с энкодером

//ID Configs
#include "pins.h"                               //Пины
#include "TASK_ID.h"                            //Задачи
#include "GUI_ID.h"                             //Меню

//GUI
#include "image.h"                              //Иконки
#include "gui_manager.h"                        //Управление меню

//Menu
#include "waiting_menu.h"                       //Меню ожидания (1 страница)
#include "waiting_menu_1.h"                     //Меню ожидания (2 страница)
#include "options_menu.h"                       //Меню настроек
#include "cmt_cfg_menu.h"                       //Меню настройки климата

//Special
#include "climate_manager.h"                    //Управление климатом
#include "led_effects.h"                        //Эффеткы светодиодов


TFT screen(CS_PIN, DC_PIN, SCRST_PIN);          //Экран
//Энкодер
Encoder enc(ENC_LEFT, ENC_RIGHT, true, ENC_BTN);

//Задача для упраления энкодером
void execute_enc_handler(int tid){
  unsigned char result = enc.tick();
  
  GM_Call_Event(&screen, result, false);
}

//Задача для обновления меню
void execute_gui_handler(int tid){
  GM_Update_Menu(&screen);
}

//Задача для управления климатом
void execute_climate_handler(int tid){
  CM_Loop();
}

//Задача для управления кнопки на энкодере
void execute_button_handler(int tid){
  enc.tickButton();
  //if(enc.buttonState == true) Serial.println(1); 
  GM_Call_Event(&screen, NONE, enc.buttonState);
}

//Регистрация заданий
void registerAllTasks(){
  RTOS_Register_Task(ENCODER_HANDLER, REPEATING, 5, execute_enc_handler);
  RTOS_Register_Task(BUTTON_HANDLER, REPEATING, 200, execute_button_handler);
  RTOS_Register_Task(CLIMATE_HANDLER, REPEATING, 100, execute_climate_handler);
  RTOS_Register_Task(GUI_UPDATER, REPEATING, 500, execute_gui_handler);
  RTOS_Register_Task(FOG_DEMO, REPEATING, 1000, CM_Fog);
  RTOS_Register_Task(LED_EFFECTS, REPEATING, 5000, CM_Update_Leds);
  RTOS_Register_Task(PUMP_DEMO, REPEATING, 1000, CM_Pump);
  RTOS_Register_Task(SENSOR_READER, REPEATING, 2000, CM_Update_Sensors);
}

void setup() {
  Serial.begin(115200);
  //Serial3.begin(115200);

  //Иницализация пинов
  pinMode(ENC_LEFT, INPUT);
  pinMode(ENC_RIGHT, INPUT);
  pinMode(ENC_BTN, INPUT_PULLUP);
  
  pinMode(FAN_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(FOG_PIN, OUTPUT);
  pinMode(DHT_PIN, OUTPUT);

  pinMode(SEN_ENABLE_PIN, OUTPUT);

  //Инициализация экрана
  screen.begin();
  screen.setRotation(3);

  CM_Init();                                        //Инициализация климата
  GM_Init(&screen);                                 //Инициализация меню
  RTOS_Init();                                      //Инициализация диспетчера задач

  //Регистрация меню
  GM_Register_Menu(WAITING_MENU_1, WM_Show, WM_Update, WM_Handle_Event);
  GM_Register_Menu(WAITING_MENU_2, WM1_Show, WM1_Update, WM1_Handle_Event);
  GM_Register_Menu(OPTIONS_MENU, OM_Show, OM_Update, OM_Handle_Event);
  GM_Register_Menu(CLIMATE_CFG_MENU, CM_Show, CM_Update, CM_Handle_Event);
  //GM_Register_Menu(WAITING_MENU_3, WM2_Show, WM2_Update, WM2_Handle_Event);
  
  registerAllTasks();                               //Регистрация всех задач
  
  GM_Show_Menu(&screen, WAITING_MENU_1);            //Показ меню ожидания (страница 1)
  
  CM_Show_LedEffect(LE_Gradient, 250);              //Показ эффекта "Градиент"
  CM_Toggle_LedEffects();                           //Включение эффектов
  CM_Toggle_FogAndPump();                           //Включение насоса и парогенератора
  
  randomSeed(analogRead(0));                        //Инициализация генератора псевдо-случайных чисел
}

void loop() {
  RTOS_Check_Tasks();                               //Проверка заданий
}
