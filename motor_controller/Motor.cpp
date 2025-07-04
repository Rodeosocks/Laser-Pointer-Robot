#include "Motor.h"

Motor::Motor(int IN1_PIN, int IN2_PIN, int EN_PIN) {
  this->IN1_PIN = IN1_PIN;
  this->IN2_PIN = IN2_PIN;
  this->EN_PIN = EN_PIN;
  int ENC_A_PIN = -1;
}

Motor::Motor(int IN1_PIN, int IN2_PIN, int EN_PIN, int ENC_A_PIN, int ENC_B_PIN, ESP32Encoder encoder) {
  this->IN1_PIN = IN1_PIN;
  this->IN2_PIN = IN2_PIN;
  this->EN_PIN = EN_PIN;
  this->ENC_A_PIN = ENC_A_PIN;
  this->ENC_B_PIN = ENC_B_PIN;
  this->encoder = encoder;
  int count = 0;
  bool prev_b = digitalRead(ENC_B_PIN);
}

void Motor::init() {
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  stop();
  if (ENC_A_PIN != -1) {
    encoder.attachHalfQuad(ENC_A_PIN, ENC_B_PIN);
    encoder.setCount(0);
  }
}

void Motor::forward(float speed) {
  speed = 1000 * constrain(speed, 0.0, 1.0);
  int speed_mapped = map(speed, 0, 1000, 0, 255);
  analogWrite(EN_PIN, speed_mapped);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN1_PIN, HIGH);
}

void Motor::backward(float speed) {
  speed = 1000 * constrain(speed, 0.0, 1.0);
  int speed_mapped = map(speed, 0, 1000, 0, 255);
  analogWrite(EN_PIN, speed_mapped);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN1_PIN, LOW);
}

void Motor::stop() {
  analogWrite(EN_PIN, 0);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
}

void Motor::print_count() {
  long newPosition = encoder.getCount() / 2;
  Serial.println(newPosition);
  delay(1);
}