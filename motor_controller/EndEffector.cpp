#include "EndEffector.h"

EndEffector::EndEffector(Motor& motor1, Motor& motor2)
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

void EndEffector::generate_trajectory(float des_roll,
                                      float des_pitch,
                                      int* enc_1_array,
                                      int* enc_2_array,
                                      int num_inputs,
                                      float time_to_pose,
                                      float control_time_step) {
  // control_time_step
  time_to_pose *= pow(10.0, 6.0);
  float p1 = 0.0;
  float current_time = 0.0;
  float init_pitch = get_pitch();
  float init_roll = get_roll();

  for (int i = 0; i < num_inputs; i++) {
    // Pre-compute the shared part of the equations
    p1 = ((-2.0 / pow(time_to_pose, 3.0)) * pow(current_time, 3.0)) + ((3.0 / pow(time_to_pose, 2.0)) * pow(current_time, 2.0));

    // Calculate encoder values
    enc_1_array[i] = int(round(((p1 * (des_pitch + des_roll - init_pitch - init_roll)) + (init_pitch + init_roll)) * (960.0 / 360.0)));
    enc_2_array[i] = int(round(((p1 * (des_roll - des_pitch + init_pitch - init_roll)) + (init_roll - init_pitch)) * (960.0 / 360.0)));

    // Increment current_time
    current_time += control_time_step;
  }
}

bool EndEffector::go_to_pose(float des_roll, float des_pitch, float time_to_pose, float control_time_step) {
  if (generated_traj == false) {
    if (abs(des_pitch) > 100.0) {
      Serial.print("\n=======================");
      Serial.print("PITCH CANNOT EXCEED 100 DEG IN MAGNITUDE\n");
      Serial.print("=======================\n");
      return true;
    }
    num_inputs = int(round((time_to_pose * pow(10.0, 6.0)) / (control_time_step)));
    Serial.print("\nNUM INPUTS: ");
    Serial.println(num_inputs);
    enc_1_array = new int[num_inputs];
    enc_2_array = new int[num_inputs];
    generate_trajectory(des_roll,
                        des_pitch,
                        enc_1_array,
                        enc_2_array,
                        num_inputs,
                        time_to_pose, 
                        control_time_step);
    generated_traj = true;
  }

  int error_1 = enc_1_array[idx] - (motor1.get_count() / 2);
  int error_2 = enc_2_array[idx] - (motor2.get_count() / 2);

  float speed_1 = error_1 * (1 / 360.0);
  float speed_2 = error_2 * (1 / 360.0);

  if (idx < (num_inputs-1)) {
    completed_move = false;

    // Command motor 1
    if (error_1 > 0) {
      motor1.forward(abs(speed_1));
    } else {
      motor1.backward(abs(speed_1));
    }

    // Command motor 2
    if (error_2 > 0) {
      motor2.forward(abs(speed_2));
    } else {
      motor2.backward(abs(speed_2));
    }

    idx++;

  } else {
    motor1.stop();
    motor2.stop();
    completed_move = true;
    generated_traj = false;
    idx = 0;
    delete[] enc_1_array;
    delete[] enc_2_array;
    enc_1_array = nullptr;
    enc_2_array = nullptr;
  }

  return completed_move;
}