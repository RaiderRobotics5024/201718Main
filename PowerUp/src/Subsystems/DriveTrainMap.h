#ifndef _DRIVE_TRAIN_MAP_HG_
#define _DRIVE_TRAIN_MAP_HG_

#include <math.h>

const bool IS_QBERT = true; // change this to false if using the test bot

const int DRIVETRAIN_LEFT_FRONT_MOTOR_ID = 1;
const int DRIVETRAIN_LEFT_REAR_MOTOR_ID = 2;
const int DRIVETRAIN_RIGHT_FRONT_MOTOR_ID = 3;
const int DRIVETRAIN_RIGHT_REAR_MOTOR_ID = 4;

const double WHEEL_RADIUS = 3.0;
const double WHEEL_TO_WHEEL = 19.75;
const double HALF_ROBOT_LENGTH = 19.00;
const int TICKS_PER_REVOLUTION = 1440; //2048; //4096;
const double INCHES_PER_REVOLUTION = 2.0 * M_PI * WHEEL_RADIUS;
const double INCHES_PER_TICK = INCHES_PER_REVOLUTION / TICKS_PER_REVOLUTION;
const int SLOT_INDEX = 0;
const int PID_LOOP_INDEX = 0;
const int TIMEOUT_MS = 100;
const int BASE_TRAJECTORY_PERIOD_MS = 0;
const int NEUTRAL_DEADBAND_PERCENT = 1;

const double TALON_PID_P = 0.03f;
const double TALON_PID_I = 0.00;
const double TALON_PID_D = 0.00;
const double TALON_PID_F = 0.00;

//Gyro Settings:
const static double GYRO_PID_P = 0.005f;
const static double GYRO_PID_I = 0.004f;
const static double GYRO_PID_D = 0.002f;
const static double GYRO_PID_F = 0.000f;

const static double GYRO_TOLERANCE_DEGREES = 1.0f;

#endif
