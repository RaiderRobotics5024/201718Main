#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

//Drive Train
const int LEFT_FRONT_MOTOR_ID = 4;
const int LEFT_REAR_MOTOR_ID = 3;
const int RIGHT_FRONT_MOTOR_ID = 1;
const int RIGHT_REAR_MOTOR_ID = 2;

const double WHEEL_RADIUS = 3.0;

const int SLOT_INDEX = 0;
const int PID_LOOP_INDEX = 0;
const int TIMEOUT_MS = 10;
const int SENSOR_UNITS_PER_ROTATION = 4096;
const int BASE_TRAJECTORY_PERIOD_MS = 0;
const int NEUTRAL_DEADBAND_PERCENT = 1;

//XBox Controller
const int XBOX_CONTROLLER_DRIVE_PORT = 0;

#endif
