#ifndef ENDEFFECTOR_H
#define ENDEFFECTOR_H

#include <Arduino.h>
#include "Motor.h"

class EndEffector {
private:
  Motor& motor1;
  Motor& motor2;
  float roll = 0.0;
  float pitch = 0.0;
  bool generated_traj = false;
  int* enc_1_array = nullptr;
  int* enc_2_array = nullptr;
  int idx = 0;
  bool completed_move = false;
  int num_inputs;

public:
  EndEffector(Motor& motor1, Motor& motor2);
  float get_roll();
  float get_pitch();
  void generate_trajectory(float des_roll,
                           float des_pitch,
                           int *enc_1_array,
                           int *enc_2_array,
                           int num_inputs,
                           float time_to_pose,
                           float control_time_step);
  bool go_to_pose(float des_roll, float des_pitch, float time_to_pose, float control_time_step);
};

#endif