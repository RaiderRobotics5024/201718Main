#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

#include <math.h>

//Drive Train
const int DRIVETRAIN_RIGHT_FRONT_MOTOR_ID = 1;
const int DRIVETRAIN_RIGHT_REAR_MOTOR_ID = 2;
const int DRIVETRAIN_LEFT_FRONT_MOTOR_ID = 3;
const int DRIVETRAIN_LEFT_REAR_MOTOR_ID = 4;

const double WHEEL_RADIUS = 3.0;
const double WHEEL_TO_WHEEL = 19.75;
const int TICKS_PER_REVOLUTION = 4096;
const double INCHES_PER_REVOLUTION = 2 * M_PI * WHEEL_RADIUS;
const int SLOT_INDEX = 0;
const int PID_LOOP_INDEX = 0;
const int TIMEOUT_MS = 10;

// Gyro Settings
const static double GYRO_PID_P = 0.03f;
const static double GYRO_PID_I = 0.00f;
const static double GYRO_PID_D = 0.00f;
const static double GYRO_PID_F = 0.00f;

const static double GYRO_TOLERANCE_DEGREES = 2.0f;

// Intake
const int INTAKE_LEFT_MOTOR_ID = 7;
const int INTAKE_RIGHT_MOTOR_ID = 6;

// Gripper
const int GRIPPER_SOLENOID_CAN_ID = 8;
const int GRIPPER_SOLENOID_FORWARDCHANNEL_ID = 2;
const int GRIPPER_SOLENOID_REVERSECHANNEL_ID = 1;

// Elevator
const int ELEVATOR_MOTOR_ID = 5;
const int ELEVATOR_TOP_SWITCH_ID = 1;
const int ELEVATOR_MID_SWITCH_ID = 2;
const int ELEVATOR_BOTTOM_SWITCH_ID = 3;

// ClimbSystem
const int CLIMBSYSTEM_MOTOR_ID = 10;
const int CLIMBSYSTEM_SOLENOID_CAN_ID = 8;
const int CLIMBSYSTEM_SOLENOID_FORWARD_CHANNEL_ID = 0;

//XBox Controller
const int XBOX_CONTROLLER_DRIVE_PORT = 0;
const int XBOX_CONTROLLER_OPERATOR_PORT = 1;
const double XBOX_DEADZONE_LEFT_JOY = 0.1;
const double XBOX_DEADZONE_RIGHT_JOY = 0.1;

#endif
