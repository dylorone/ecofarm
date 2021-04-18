#ifndef wifi_mgt_h
#define wifi_mgt_h

#include<Arduino.h>

//Стадии работы с WiFi
struct WIFI_Stage {
  unsigned char id;
  unsigned int times_called;
  int (*run_)(unsigned int times);
};

static bool stagesEnabled = true;
static WIFI_Stage stages[10];
static unsigned char currentStage;

void WIFI_Init();                     //Инициализация WiFi
void WIFI_Loop();                     //Обработка WiFi

WIFI_Stage Create_WIFI_Stage(unsigned char id, int (*run_)(unsigned int times));

int WIFI_WaitForBoot(unsigned int times);
int WIFI_WaitForConnect(unsigned int times);
int WIFI_ConnectToServer(unsigned int times);
int WIFI_SendTest(unsigned int times);

#endif
