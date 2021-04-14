#ifndef encoder_h
#define encoder_h

#define NONE 0
#define ROTATE_LEFT 1
#define ROTATE_RIGHT 2

#define PRESS 1

class Encoder {
  private:
  unsigned char pinStatesAway = 0;
  bool leftPinStates[4];
  bool rightPinStates[4];
  bool lastButtonState;
  
  public:
  unsigned char pinLeft;
  unsigned char pinRight;
  bool hasButton;
  unsigned char pinButton;

  unsigned char encState;
  bool buttonState;

  Encoder(unsigned char pinLeft, unsigned char pinRight, bool hasButton=false, unsigned char pinButton=0);
  unsigned char tick();
  void tickButton();
  bool isSomethingChanged(bool pinLeftState, bool pinRightState);
};

void clearArray(bool *arr, unsigned char len);

#endif
