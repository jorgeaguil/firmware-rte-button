#ifndef Leds_h
#define Leds_h

#define LED_ROJO 26
#define LED_VERDE 25

class Leds {
public:
  void init(void);
};

void Leds::init(void) {
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
}

#endif
