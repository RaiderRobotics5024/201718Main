#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

#include <math.h>

//Drive Train
const bool IS_QBERT = true; // change this to false if using the test bot

const int DRIVETRAIN_LEFT_FRONT_MOTOR_ID = 1;
const int DRIVETRAIN_LEFT_REAR_MOTOR_ID = 2;
const int DRIVETRAIN_RIGHT_FRONT_MOTOR_ID = 3;
const int DRIVETRAIN_RIGHT_REAR_MOTOR_ID = 4;

const double WHEEL_RADIUS = 3.0;
const double WHEEL_TO_WHEEL = 19.75;
const double HALF_ROBOT_LENGTH = 19.00;
const int TICKS_PER_REVOLUTION = 8152; //4096;
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

// Gyro Settings
const static double GYRO_PID_P = 0.005f;
const static double GYRO_PID_I = 0.004f;
const static double GYRO_PID_D = 0.002f;
const static double GYRO_PID_F = 0.000f;

const static double GYRO_TOLERANCE_DEGREES = 1.0f;

// Intake
const int INTAKE_LEFT_MOTOR_ID = 7;
const int INTAKE_RIGHT_MOTOR_ID = 6;

// Gripper
const int GRIPPER_SOLENOID_CAN_ID = 8;
const int GRIPPER_SOLENOID_FORWARDCHANNEL_ID = 2;
const int GRIPPER_SOLENOID_REVERSECHANNEL_ID = 1;
const double GRIPPER_SPEED_ADJUSTMENT_RATIO = 0.75;

// Elevator
const int ELEVATOR_MOTOR_ID = 5;
const int ELEVATOR_TOP_SWITCH_ID = 3;
const int ELEVATOR_MID_SWITCH_ID = 2;
const int ELEVATOR_BOTTOM_SWITCH_ID = 4;

// ClimbSystem
const int CLIMBSYSTEM_MOTOR_ID = 10;
const int CLIMBSYSTEM_SOLENOID_CAN_ID = 8;
const int CLIMBSYSTEM_SOLENOID_FORWARD_CHANNEL_ID = 0;

// Compressor
const int COMPRESSOR_ID = 8;

//XBox Controller
const int XBOX_CONTROLLER_DRIVE_PORT = 0;
const int XBOX_CONTROLLER_OPERATOR_PORT = 1;
const double XBOX_DEADZONE_LEFT_JOY = 0.1;
const double XBOX_DEADZONE_RIGHT_JOY = 0.1;

#endif
