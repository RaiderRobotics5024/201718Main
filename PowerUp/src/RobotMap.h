#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

//Drive Train
const int DRIVETRAIN_RIGHT_FRONT_MOTOR_ID = 1;
const int DRIVETRAIN_RIGHT_REAR_MOTOR_ID = 2;
const int DRIVETRAIN_LEFT_FRONT_MOTOR_ID = 3;
const int DRIVETRAIN_LEFT_REAR_MOTOR_ID = 4;

const double WHEEL_RADIUS = 3.0;

// Intake
const int INTAKE_LEFT_MOTOR_ID = 7;
const int INTAKE_RIGHT_MOTOR_ID = 6;

// The pnuematic dolenoid valve
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
//const int CLIMBSYSTEM_SOLENOID_REVERSE_CHANNEL_ID = 1;


//XBox Controller
const int XBOX_CONTROLLER_DRIVE_PORT = 0;
const int XBOX_CONTROLLER_OPERATOR_PORT = 1;
//controller deadzone
const double XBOX_DEADZONE_LEFT_JOY = 0.1;
const double XBOX_DEADZONE_RIGHT_JOY = 0.1;


#endif

