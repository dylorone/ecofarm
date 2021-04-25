#ifndef climate_manager_h
#define climate_manager_h

#include<iarduino_RTC.h>
#include<DHT.h>
#include<FastLED.h>

#include "pins.h"


#define NUM_LEDS 46
#define DIRT_HUMIDITY 70

/*
  WL_ALARM = WLALARM_PIN,
  WL_MAX = WLMAX_PIN,
  WL_MIN = WLMIN_PIN,
  DH_SENSOR = DIRT_HUMIDITY_PIN
 */

typedef struct LedEffect {
  bool dec;
  unsigned char exec_times;
  unsigned char occs_away;
  unsigned int (*exec)(CRGB* leds, unsigned char occ);
};

static LedEffect currentLedEffect;
static boolean effectsEnabled = false;

static boolean fogEnabled = false;
static boolean pumpEnabled = false;

static boolean fogState = false;
static boolean pumpState = false;

enum Sensor {
  WL_ALARM,
  WL_MAX,
  WL_MIN,
  DH_SENSOR
};

static String current_time;
static String temperature;
static String airHumidity;
static unsigned char dirtHumidity;

static iarduino_RTC watch(RTC_DS1302, RST_PIN, CLK_PIN, DAT_PIN);
static DHT dht_sensor(DHT_PIN, DHT22);
static CRGB leds[NUM_LEDS];


void CM_Init();
void CM_Loop();

void CM_Show_LedEffect(unsigned int (*exec)(CRGB* leds, unsigned char occ), unsigned char occs_amount);
void CM_Toggle_LedEffects();
void CM_Update_Leds(int tid);

void CM_Fog(int tid);
void CM_Pump(int tid);
void CM_Toggle_FogAndPump();

String CM_Get_Time();
String CM_Get_Temperature();
String CM_Get_AirHumidity();
String CM_Get_DirtHumidity();
unsigned char CM_Read_WSensor(Sensor sensor);

#endif
