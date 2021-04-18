#include "wifi_mgt.h"

#include <Arduino.h>

#include "serialutils.h"

const String connProtocol = "TCP";
const String ip = "192.168.1.198";
const int port = 8000;

WIFI_Stage Create_WIFI_Stage(unsigned char id, int (*run_)(unsigned int times)){
  WIFI_Stage result = {id, 0, run_};
  return result;
}

void WIFI_Init(){

  stages[0] = Create_WIFI_Stage(0, WIFI_WaitForBoot);
  stages[1] = Create_WIFI_Stage(1, WIFI_WaitForConnect);
  stages[3] = Create_WIFI_Stage(3, WIFI_ConnectToServer);
  stages[4] = Create_WIFI_Stage(4, WIFI_SendTest);

  currentStage = 0;
}

void WIFI_Loop(){
  if(stagesEnabled){
    int result = stages[currentStage].run_(stages[currentStage].times_called);
    stages[currentStage].times_called = stages[currentStage].times_called + 1;
    if(result != -1) currentStage = result;
  }
}

int WIFI_WaitForBoot(unsigned int times){
  if(times == 0){
    Serial3.println("AT+RST");
    Serial.println("RST");
    return -1;
  }

  if(!Serial3.available()){
    Serial.println("No info");
    return -1;
  } 

  String result = Serial3.readString();
  if(result.indexOf("WIFI CONNECTED") != -1 || result.indexOf("ready") != -1){
    Serial.println("WIFI CONNECTED");
    return 3;
  }
  Serial.println("???");
  return -1;
}

int WIFI_WaitForConnect(unsigned int times){
  Serial.println("WaitForConnect");

  if(!Serial3.available() && times < 6) return -1;

  if(Serial3.available()){
    if(!Serial3.find("WIFI CONNECTED")) return -1;
    else{
      Serial.println("WIFI CONNECT!");
      return 3;
    } 
  }
  if(times >= 6) return 2;
}

int WIFI_ConnectToServer(unsigned int times){
  Serial.println("Connect to server...");
  if(times == 0){
    Serial3.println("AT+CIPSTART=\"" + connProtocol + "\",\"" + ip + "\"," + String(port));
    Serial.println("AT+CIPSTART=\"" + connProtocol + "\",\"" + ip + "\"," + String(port));
  }
  if(!Serial3.available()) return -1;

  String result = Serial3.readString();
  if(result.indexOf("CONNECT") != -1 || result.indexOf("OK") != -1){
    Serial.println("Success!");
    return 4;
  }

  Serial.println(":(");
  return -1;
}

int WIFI_SendTest(unsigned int times){
  if(times == 0){
    Serial3.println("AT+CIPSEND=2");
    Serial.println("Sending...");
    return -1;
  }

  if(!Serial3.available()) return -1;

  String read = Serial3.readString();

  if(read.indexOf(">") != -1){
    byte tosend[2] = {0x1, 0x2};
    Serial3.write(tosend, 2);
    return -1;
  }

  else if(read.indexOf("SEND FAIL") != -1){
    Serial.println("FAIL");
  }

  else if(read.indexOf("SEND OK") != -1){
    Serial.println("OK");
  }

  stagesEnabled = false;
  return 0;
}
