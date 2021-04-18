#include "encoder.h"
#include "Arduino.h"

Encoder::Encoder(unsigned char pinLeft, unsigned char pinRight, bool hasButton=false, unsigned char pinButton=0){
  this->pinLeft = pinLeft;
  this->pinRight = pinRight;
  this->hasButton = hasButton;
  this->pinButton = pinButton;
}

unsigned char Encoder::tick(){
  bool pinLeftState = !digitalRead(pinLeft);
  bool pinRightState = !digitalRead(pinRight);

  if(this->isSomethingChanged(pinLeftState, pinRightState) == false){
    encState = NONE;
    return NONE;
  }

  if(pinStatesAway < 3){
    leftPinStates[pinStatesAway] = pinLeftState;
    rightPinStates[pinStatesAway] = pinRightState;
    pinStatesAway++;
    encState = NONE;
    return NONE;
  }

  if(leftPinStates[0] == 1 && rightPinStates[0] == 0){
    pinStatesAway = 0;
    clearArray(leftPinStates, 4);
    clearArray(rightPinStates, 4);
    encState = ROTATE_LEFT;
    return ROTATE_LEFT;
  }

  if(leftPinStates[0] == 0 && rightPinStates[0] == 1){
    pinStatesAway = 0;
    clearArray(leftPinStates, 4);
    clearArray(rightPinStates, 4);
    encState = ROTATE_RIGHT;
    return ROTATE_RIGHT;
  }

  pinStatesAway = 0;
  clearArray(leftPinStates, 4);
  clearArray(rightPinStates, 4);

  encState = NONE;
  return NONE;
}

void Encoder::tickButton(){
  if(!hasButton) return;
  bool state = !digitalRead(pinButton);
  if(lastButtonState != state && state == HIGH) buttonState = state;
  if(buttonState == HIGH && lastButtonState == state) buttonState = LOW;
  lastButtonState = state;
}

bool Encoder::isSomethingChanged(bool pinLeftState, bool pinRightState){
  if(pinStatesAway == 0){
    if(pinLeftState == true || pinRightState == true) return true;
  }

  else{
    if(pinLeftState != leftPinStates[pinStatesAway-1] || pinRightState != rightPinStates[pinStatesAway-1]){
      return true;
    }
  }

  return false;
}

void clearArray(bool *arr, unsigned char len){
  for(int i=0;i<len;i++){
    arr[i] = 0;
  }
}
