#include "EndEffector.h"

EndEffector::EndEffector(Motor motor1, Motor motor2)
  : motor1(motor1), motor2(motor2) {
}

float EndEffector::get_roll() {
  // Sign of the output assumes motor1 is on the left,
  // and motor2 is on the right
  float m1_angle = motor1.get_angle();
  float m2_angle = motor2.get_angle();
  return ((m1_angle + m2_angle) / 2);
}

float EndEffector::get_pitch() {
  // Sign of the output assumes motor1 is on the left,
  // and motor2 is on the right
  float m1_angle = motor1.get_angle();
  float m2_angle = motor2.get_angle();
  return ((m1_angle - m2_angle) / 2);
}