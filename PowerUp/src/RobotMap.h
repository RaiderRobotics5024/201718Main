#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

// Drive Train
const int LEFT_FRONT_MOTOR_ID = 1;
const int LEFT_REAR_MOTOR_ID = 2;
const int RIGHT_FRONT_MOTOR_ID = 3;
const int RIGHT_REAR_MOTOR_ID = 4;

// Talon Settings
const double WHEEL_RADIUS = 3.0; // in inches
const int TICKS_PER_REVOLUTION = 4096;
const double INCHES_PER_REVOLUTION = 18.85; // 2 * r * pi in inches
const int SLOT_INDEX = 0;
const int PID_LOOP_INDEX = 0;
const int TIMEOUT_MS = 10;

// Gyro Settings
const static double PID_P = 0.03f;
const static double PID_I = 0.00f;
const static double PID_D = 0.00f;
const static double PID_F = 0.00f;

const static double TOLERANCE_DEGREES = 2.0f;



// XBox Controller
const int XBOX_CONTROLLER_DRIVE_PORT = 0;

#endif
