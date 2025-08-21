// Import classes
#include "Motor.h"
#include "EndEffector.h"

// Declare pin numbers
// Motor 1
int enA = 15;
int in1 = 3;
int in2 = 0;
int enc1A = 21;
int enc1B = 19;
// Motor 2
int enB = 17;
int in3 = 4;
int in4 = 16;
int enc2A = 18;
int enc2B = 5;

// Initialize global varaibles
bool completed_move = false;
float control_time_step = 1000.0; // microseconds
unsigned long prev_time;
unsigned long time_diff;
bool already_printed = false;

// Instatiate objects
// Create encoder objects
ESP32Encoder encoder1;
ESP32Encoder encoder2;
// Create motor objects
Motor motor1(in1, in2, enA, enc1A, enc1B, encoder1);
Motor motor2(in3, in4, enB, enc2A, enc2B, encoder2);
// Create end effector object
EndEffector camera(motor1, motor2);

void setup() {
  Serial.begin(115200);
  motor1.init();
  motor2.init();
  prev_time = micros();
}

void loop() {
  time_diff = micros() - prev_time;

  
  if ((completed_move == false) && (time_diff >= control_time_step)) {
    completed_move = camera.go_to_pose(0.0, -90.0, 0.5, control_time_step);
    prev_time = micros();
  } else if ((completed_move == true) && (already_printed == false)) {
    Serial.println("Move Complete");
    already_printed = true;
  }
}
