// button.h
#ifndef Button_h
#define Button_h

#define EMERGENCY_BUTTON 33

class EmergencyButton {
public:
  void init(void);
};

void EmergencyButton::init(void) {
  pinMode(EMERGENCY_BUTTON, INPUT);
}

#endif
