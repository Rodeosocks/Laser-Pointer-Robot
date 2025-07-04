#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <ESP32Encoder.h>

class Motor {
private:
  int IN1_PIN;
  int IN2_PIN;
  int EN_PIN;
  int ENC_A_PIN;
  int ENC_B_PIN;
  ESP32Encoder encoder;

public:
  Motor(int IN1_PIN, int IN2_PIN, int EN_PIN);
  Motor(int IN1_PIN, int IN2_PIN, int EN_PIN, int ENC_A_PIN, int ENC_B_PIN, ESP32Encoder encoder);
  void init();
  void forward(float speed);
  void backward(float speed);
  void stop();
  void print_count();
};

#endif