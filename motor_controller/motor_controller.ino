// Import classes
#include "Motor.h"

// Declare pin numbers
// Motor 1
int enA = 17;
int in1 = 16;
int in2 = 4;
int enc1A = 21;
int enc1B = 19;
// Motor 2
int enB = 15;
int in3 = 0;
int in4 = 3;
int enc2A = 18;
int enc2B = 5;

// Initialize global varaibles
int state = 0;
bool completed_move_m1 = false;
bool completed_move_m2 = false;
bool completed_move = false;

// Instatiate objects
// Create encoder objects
ESP32Encoder encoder1;
ESP32Encoder encoder2;
// Create motor objects
Motor motor1(in1, in2, enA, enc1A, enc1B, encoder1);
Motor motor2(in3, in4, enB, enc2A, enc2B, encoder2);

void setup() {
  Serial.begin(115200);
  motor1.init();
  motor2.init();
}

void loop() {
  switch (state) {
    case 0:
      {
        if ((completed_move_m1 == false) || (completed_move_m2 == false)) {
          // Serial.println("Executing state 0");
          if (completed_move_m1 == false) {
            completed_move_m1 = motor1.go_to_angle(90.0);
          }
          if (completed_move_m2 == false) {
            completed_move_m2 = motor2.go_to_angle(90.0);
          }
        } else {
          state = 1;
          completed_move_m1 = false;
          completed_move_m2 = false;
          Serial.println("\n--- Yaw0 rotation complete ---\n");
          delay(1000);
        }
      }
      break;

    case 1:
      {
        if ((completed_move_m1 == false) || (completed_move_m2 == false)) {
          // Serial.println("Executing state 1");
          if (completed_move_m1 == false) {
            completed_move_m1 = motor1.go_to_angle(-90.0);
          }
          if (completed_move_m2 == false) {
            completed_move_m2 = motor2.go_to_angle(90.0);
          }
        } else {
          state = 2;
          completed_move_m1 = false;
          completed_move_m2 = false;
          Serial.println("\n--- Pitch1 rotation complete ---\n");
          delay(1000);
        }
      }
      break;

    case 2:
      {
        if ((completed_move_m1 == false) || (completed_move_m2 == false)) {
          // Serial.println("Executing state 3");
          if (completed_move_m1 == false) {
            completed_move_m1 = motor1.go_to_angle(-270.0);
          }
          if (completed_move_m2 == false) {
            completed_move_m2 = motor2.go_to_angle(-270.0);
          }
        } else {
          state = 3;
          completed_move_m1 = false;
          completed_move_m2 = false;
          Serial.println("\n--- Yaw2 rotation complete ---\n");
          delay(1000);
        }
      }
      break;

    case 3:
      {
        if ((completed_move_m1 == false) || (completed_move_m2 == false)) {
          // Serial.println("Executing state 3");
          if (completed_move_m1 == false) {
            completed_move_m1 = motor1.go_to_angle(90.0);
          }
          if (completed_move_m2 == false) {
            completed_move_m2 = motor2.go_to_angle(-90.0);
          }
        } else {
          state = 0;
          completed_move_m1 = false;
          completed_move_m2 = false;
          Serial.println("\n--- Pitch3 rotation complete ---\n");
          delay(1000);
        }
      }
      break;
  }
}
