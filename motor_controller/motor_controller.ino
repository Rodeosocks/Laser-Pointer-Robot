// Import classes
#include "Motor.h"

// Declare pin numbers
// Motor 1
int enA = 17;
int in1 = 16;
int in2 = 4;

// Motor 2
int enB = 15;
int in3 = 0;
int in4 = 2;
int encA = 18;
int encB = 5;

// Create encoder objects
ESP32Encoder encoder2;

// Create motor objects
Motor motor1(in1, in2, enA);
Motor motor2(in3, in4, enB, encA, encB, encoder2);

void setup() {
  Serial.begin(115200);
  motor1.init();
  motor2.init();
  motor2.forward(0.3);
}

void loop() {
  motor2.print_count();
  // Serial.println("speed=30%, 100%");
  // motor1.backward(0.3);
  // motor2.forward(1.0);
  // delay(2000);

  // Serial.println("speed=40%, 90%");
  // motor1.backward(0.4);
  // motor2.forward(0.9);
  // delay(2000);

  // Serial.println("speed=50%, 80%");
  // motor1.backward(0.5);
  // motor2.forward(0.8);
  // delay(2000);

  // Serial.println("speed=60%, 70%");
  // motor1.backward(0.6);
  // motor2.forward(0.7);
  // delay(2000);

  // Serial.println("speed=70%, 60%");
  // motor1.backward(0.7);
  // motor2.forward(0.6);
  // delay(2000);

  // Serial.println("speed=80%, 50%");
  // motor1.backward(0.8);
  // motor2.forward(0.5);
  // delay(2000);

  // Serial.println("speed=90%, 40%");
  // motor1.backward(0.9);
  // motor2.forward(0.4);
  // delay(2000);

  // Serial.println("speed=100%, 30%");
  // motor1.backward(1.0);
  // motor2.forward(0.3);
  // delay(2000);

  // Serial.println("--- OFF ---\n");
  // motor1.stop();
  // motor2.stop();
  // delay(5000);
}