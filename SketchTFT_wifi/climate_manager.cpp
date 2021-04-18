#include "climate_manager.h"

#include "RTOSlib.h"

#include<Arduino.h>
#include<math.h>

#include<iarduino_RTC.h>
#include<DHT.h>
#include<FastLED.h>

#include "pins.h"

void CM_Init(){
  watch.begin();
  //watch.settime(0, 0, 15, 12, 2, 21, 5);
  
  dht_sensor.begin();
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();
}

void CM_Loop(){
  current_time = watch.gettime("H:i");

  float temp = dht_sensor.readTemperature();
  float hum = dht_sensor.readHumidity();
  if(isnanf(temp)) temperature = "N/A";
  else temperature = String(temp).substring(0, 4);

  if(isnanf(hum)) airHumidity = "N/A";
  else airHumidity = String(hum).substring(0, 4);

  digitalWrite(SEN_ENABLE_PIN, HIGH);
  dirtHumidity = analogRead(DIRT_HUMIDITY_PIN)/4;
  digitalWrite(SEN_ENABLE_PIN, LOW);

  //if(effectsEnabled) CM_Update_Leds();

  /*digitalWrite(SEN_ENABLE_PIN, HIGH);
  dirtHumidity = String(analogRead(DIRT_HUMIDITY_PIN)/4);
  Serial.print("ALARM = ");
  Serial.print(analogRead(WLALARM_PIN));
  Serial.print(" | MAX = ");
  Serial.print(analogRead(WLMAX_PIN));
  Serial.print(" | VARIABLE = ");
  Serial.println(analogRead(VARIABLE_PIN));
  digitalWrite(SEN_ENABLE_PIN, LOW);*/
}

void CM_Update_Leds(int tid){
  if(!effectsEnabled) return;
  
  rtos_tasks[tid].exec_time = currentLedEffect.exec(leds, currentLedEffect.occs_away);
  if(currentLedEffect.occs_away == currentLedEffect.exec_times) currentLedEffect.dec = true;
  else if(currentLedEffect.occs_away == 0) currentLedEffect.dec = false;
    
  if(currentLedEffect.dec == false) currentLedEffect.occs_away++;
  else if(currentLedEffect.dec == true) currentLedEffect.occs_away--;

  fogEnabled = false;
  pumpEnabled = false;
}

void CM_Show_LedEffect(unsigned int (*exec)(CRGB* leds, unsigned char occ), unsigned char occs_amount){
  currentLedEffect = {false, occs_amount, 0, exec};
}

void CM_Fog(int tid){
  if(!fogEnabled) return;
  
  digitalWrite(FOG_PIN, HIGH);
  if(!fogState) rtos_tasks[tid].exec_time = random(3, 11)*1000;
  else rtos_tasks[tid].exec_time = random(1, 6)*1000;
  
  digitalWrite(FAN_PIN, fogState);
  fogState = !fogState;
}

void CM_Pump(int tid){
  if(!pumpEnabled) return;
  if(dirtHumidity <= DIRT_HUMIDITY){
    digitalWrite(PUMP_PIN, LOW);
    return;
  }
  
  digitalWrite(PUMP_PIN, pumpState);

  if(!pumpState) rtos_tasks[tid].exec_time = 10000;
  else rtos_tasks[tid].exec_time = 800;
  
  pumpState = !pumpState;
}

void CM_Toggle_LedEffects(){
  effectsEnabled = !effectsEnabled;
}

void CM_Toggle_FogAndPump(){
  pumpEnabled = !pumpEnabled;
  fogEnabled = !fogEnabled;
}

String CM_Get_Time(){
  return current_time;
}

String CM_Get_Temperature(){
  return temperature;
}

String CM_Get_AirHumidity(){
  return airHumidity;
}

String CM_Get_DirtHumidity(){
  return String(dirtHumidity);
}
