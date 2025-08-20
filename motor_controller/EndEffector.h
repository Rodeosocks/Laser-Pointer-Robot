#ifndef ENDEFFECTOR_H
#define ENDEFFECTOR_H

#include <Arduino.h>
#include "Motor.h"

class EndEffector {
private:
  Motor motor1;
  Motor motor2;
  float roll;
  float pitch;

public:
  EndEffector(Motor motor1, Motor motor2);
  float get_roll();
  float get_pitch();
};

#endif