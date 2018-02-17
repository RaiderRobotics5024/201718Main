#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

//Drive Train
const int DRIVETRAIN_LEFT_FRONT_MOTOR_ID = 4;
const int DRIVETRAIN_LEFT_REAR_MOTOR_ID = 3;
const int DRIVETRAIN_RIGHT_FRONT_MOTOR_ID = 1;
const int DRIVETRAIN_RIGHT_REAR_MOTOR_ID = 2;

const double WHEEL_RADIUS = 3.0;

//Intake
const int INTAKE_LEFT_MOTOR_ID = 7;		// TODO: This been assigned, yet
const int INTAKE_RIGHT_MOTOR_ID = 6;	// TODO: This hasn't been assigned, yet
// The pnuematic solenoid valve
const int GRIPPER_SOLENOID_FORWARDCHANNEL_ID = 2;
const int GRIPPER_SOLENOID_REVERSECHANNEL_ID = 1;
const int GRIPPER_SOLENOID_CAN_ID = 8;
// TODO: Add the hall effect (or whatever) sensor IDs

//Elevator
const int ELEVATOR_MOTOR_ID = 9;

//BotClimb
const int CLIMB_MOTOR_ID = 10;


//XBox Controller
const int XBOX_CONTROLLER_DRIVE_PORT = 0;
const int XBOX_CONTROLLER_OPERATOR_PORT = 1;
//controller deadzone
const double XBOX_DEADZONE_LEFT_JOY=0.1;
const double XBOX_DEADZONE_RIGHT_JOY=0.1;


#endif
