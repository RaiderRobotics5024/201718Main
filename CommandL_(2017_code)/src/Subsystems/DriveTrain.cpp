#include "DriveTrain.h"
#include "../RobotMap.h"
#include "Commands/JoystickDrive.h"
#include "math.h"

DriveTrain::DriveTrain() :
Subsystem("DriveTrain")
{
	pLeftFrontMotor = new CANTalon(TALON_LEFT_FRONT_DRIVE);
	pLeftRearMotor = new CANTalon(TALON_LEFT_REAR_DRIVE);
	pRightFrontMotor = new CANTalon(TALON_RIGHT_FRONT_DRIVE);
	pRightRearMotor = new CANTalon(TALON_RIGHT_REAR_DRIVE);

	pDipSwitchOne = new DigitalInput(0);
	pDipSwitchTwo = new DigitalInput(1);
	pDipSwitchThree = new DigitalInput(2);
	pDipSwitchFour = new DigitalInput(3);

	pLED1 = new DigitalOutput(14);

	// Assigns the Talons a device to receive feedback from
	pLeftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	pRightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);

	// Only front motor Talons have encoders


	// Encoder Pulses [SET PHYSICALLY USING DIP SWITCHES]
	pLeftFrontMotor->ConfigEncoderCodesPerRev(2048);
	pRightFrontMotor->ConfigEncoderCodesPerRev(2048);

	pGyro = new ADXRS450_Gyro();

	// Default sensitivity
	pGyro->Reset();

	pRobot = new RobotDrive(pLeftFrontMotor, pLeftRearMotor, pRightFrontMotor, pRightRearMotor);
	pRobot->SetSafetyEnabled(false);
	isReversed = true;
	pRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	pRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	pRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	pRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

	minErrorToMove = 0;

}

void DriveTrain::ReverseDrive(bool reverse){
	pRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, reverse);
	pRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, reverse);
	pRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, reverse);
	pRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, reverse);
	isReversed = reverse;
}

bool DriveTrain::IsReversed(){
	return isReversed;
}

void DriveTrain::InitDefaultCommand()
{
	SetDefaultCommand(new JoystickDrive()); //drive and tracks all triggers and D-Pad
}

void DriveTrain::Drive(Joystick* stick){
	double joyThreshold = 0.1;
	double reverseSign; // 1.0 for not reverse, -1.0 for reverse
	if(isReversed){
		reverseSign = 1.0;
	}else{
		reverseSign = -1.0; //for some reason, if you don't set motor inverse, joy X is reversed...
	}

	//copied from 2015 java project
	double stickX = stick->GetRawAxis(XBOX_L_XAXIS) * reverseSign;
	double stickY = stick->GetRawAxis(XBOX_L_YAXIS);
	SmartDashboard::PutNumber("Joy X", stickX);
	SmartDashboard::PutNumber("Joy Y", stickY);
	if(abs(stickX) > joyThreshold|| abs(stickY) > joyThreshold || true){ //debugging
		pRobot->ArcadeDrive(stickY, stickX, false);
	}else{
		pRobot->ArcadeDrive(0, 0, false);
	}

}






bool DriveTrain::GoUltraForward(double distance, float baseSpeed, double target, double kP, double source){ // THIS IS WORKING!! DO NOT OVERWRITE!!!!!!!!!!!!!!!!!!!!!!!

	double absoluteTolerance = 0.02; //in cms
	double showDownZone = 2.0;
	double showDownError = 1.0;


	SmartDashboard::PutString("Current Task", "e_automove");

	double currentDistance = source; //return value in meteres with temp compensation

	if(abs(currentDistance - distance) < showDownZone){
		showDownError = pow((double)(abs(currentDistance*1000 - distance * 1000))/(1000.0 * showDownZone),(0.5));
	}else{
		showDownError = 1.0;
	}
	SmartDashboard::PutNumber("ShowDownError", showDownError);

	if ( showDownError < minErrorToMove ) // the minimum speed you want (to get robot moving, maybe)
	{
		showDownError = 0.9 * minErrorToMove;
	}

	double directionSpeed;
	double goingBack; //i'm confused which way is front, but i'm glad that I'm not the only one
	if(distance < currentDistance){
		goingBack = 1;
		directionSpeed = -baseSpeed;
	}else{
		directionSpeed = baseSpeed; //don't ask
		goingBack = 0;
	}

	SmartDashboard::PutNumber("abs", abs(currentDistance*10 - distance*10));
	SmartDashboard::PutNumber("absoluteTolerance", absoluteTolerance);


	int angleDiff = ((int)(GetGyro() - target)) % 360;




	double error = (((double)abs(abs(angleDiff) -  180)/180.0) * 2 - 1.0) * kP; //1.0 - -1.0 //kP must be =< 1.0

	if(((angleDiff > 0 && angleDiff <= 180) || (angleDiff < -180)) && abs(currentDistance*100 - distance*100)>=absoluteTolerance){
		if(goingBack){
			TankDrive(directionSpeed * error * showDownError, directionSpeed * showDownError);
		}else{
			TankDrive(directionSpeed * showDownError, directionSpeed * error * showDownError);
		}
	}
	else if(((angleDiff < 0 && angleDiff >= -180) || (angleDiff > 180)) && abs(currentDistance*100 - distance*100)>=absoluteTolerance){
		if(goingBack){
			TankDrive(directionSpeed * showDownError, directionSpeed * error * showDownError);
		}else{
			TankDrive(directionSpeed * error * showDownError, directionSpeed * showDownError);
		}
	}
	else if(angleDiff == 0  && abs(currentDistance*100 - distance*100)>=absoluteTolerance){
		TankDrive(directionSpeed * showDownError, directionSpeed * showDownError);
	}
	else{
		TankDrive(0.0f, 0.0f);
		return true;
	}


	if(GetRightSpeed() == 0){
		minErrorToMove += 0.1;
	}

	return false;

}

bool DriveTrain::GoForward(double distance, float baseSpeed, double targetAngle, double kP){ // THIS IS WORKING!! DO NOT OVERWRITE!!!!!!!!!!!!!!!!!!!!!!!

	double absoluteTolerance = 10;
	SmartDashboard::PutString("Current Task", "automove");
	double currentDistance = GetRightEncoderValue();
	SmartDashboard::PutNumber("Enc_Goforward", currentDistance);

	double directionSpeed;
	double goingBack; //i'm confused which way is front, but i'm glad that I'm not the only one
	if(distance > currentDistance){
		goingBack = 1;
		directionSpeed = -baseSpeed;
	}else{
		directionSpeed = baseSpeed; //don't ask
		goingBack = 0;
	}

	SmartDashboard::PutNumber("EncoderReading", currentDistance);
	SmartDashboard::PutNumber("Goalz", distance);


	//	int angleDiff = ((int)(GetGyro() - target)) % 360;
	double angleDiff = GetGyro() - targetAngle;
	while (angleDiff >  360.0)	{	angleDiff -= 360.0; }
	while (angleDiff < -360.0)	{ 	angleDiff += 360.0; }



	//	double error = (((double)fabs(fabs(angleDiff) - goingBack * 180.0)/180.0) * 2 - 1.0) * kP; //1.0 - -1.0 //kP must be =< 1.0

	double error = (((double)fabs(fabs(angleDiff) - 180.0)/180.0) * 2 - 1.0) * kP; //1.0 - -1.0 //kP must be =< 1.0

	SmartDashboard::PutNumber("Debug: Gyro Raw", GetGyro());
	SmartDashboard::PutNumber("Debug: angleDiff", (double)(angleDiff));
	SmartDashboard::PutNumber("Debug: going back", (double)goingBack);
	SmartDashboard::PutNumber("Debug: raw error", (double)fabs(fabs(angleDiff) - goingBack * 180.0)/180.0);

	// Are we there yet?
	const float ANGLEERROREPSILON = 0.5;	// 0.5 degrees
	if ( fabs(currentDistance - distance) >= absoluteTolerance )
	{	// Drive and turn (if needed)
		if ( fabs(angleDiff) <= ANGLEERROREPSILON )
		{	// We are within the tolerance of angle, so drive straight forward
			SmartDashboard::PutString("GoForward_State:", "Drive straight");
			TankDrive(directionSpeed, directionSpeed);
		}
		else if ((angleDiff > ANGLEERROREPSILON && angleDiff <= 180.0) || (angleDiff < -180.0))
		{	// turn one way
			SmartDashboard::PutString("GoForward_State:", "Drive, Left turn");
			if(goingBack){
				TankDrive(directionSpeed * error, directionSpeed);
			}else{
				TankDrive(directionSpeed, directionSpeed * error);
			}
		}
		else if ((angleDiff < ANGLEERROREPSILON && angleDiff >= -180.0) || (angleDiff > 180.0))
		{
			SmartDashboard::PutString("GoForward_State:", "Drive, Right turn");
			if(goingBack){
				TankDrive(directionSpeed, directionSpeed * error);
			}else{
				TankDrive(directionSpeed * error, directionSpeed);
			}
		}
	}
	else
	{	//
		SmartDashboard::PutString("GoForward_State:", "Drive forward done");
		TankDrive(0.0f, 0.0f);
		return true;
	}


	//	if(((angleDiff > 0 && angleDiff <= 180.0) || (angleDiff < -180.0)) && fabs(currentDistance - distance)>=absoluteTolerance){
	//		TankDrive(directionSpeed * error, directionSpeed);
	//	}
	//	else if(((angleDiff < 0 && angleDiff >= -180.0) || (angleDiff > 180.0)) && fabs(currentDistance - distance)>=absoluteTolerance){
	//		TankDrive(directionSpeed, directionSpeed * error);
	//	}
	//	else if(angleDiff == 0  && fabs(currentDistance - distance)>=absoluteTolerance){
	//		TankDrive(directionSpeed, directionSpeed);
	//	}
	//	else{
	//		TankDrive(0.0f, 0.0f);
	//		return true;
	//	}
	return false;

}



bool DriveTrain::AutoTurn(double target, double kP){ // THIS IS WORKING!! DO NOT OVERWRITE!!!!!!!!!!!!!!!!!!!!!!!

	SmartDashboard::PutString("Current Task", "auto turn");

	int angleDiff = ((int)(GetGyro()-target)) % 360 ; //angle diff
	double error = (1 - (( (double) abs( abs(angleDiff) - 180 ) / 180.0))) * kP;

	if(((angleDiff > 0 && angleDiff <= 180) || (angleDiff < -180))){
		TankDrive(((0.1 * error) + 0.9), -(0.1 * error + 0.9));
	}
	else if(((angleDiff < 0 && angleDiff >= -180) || (angleDiff > 180))){
		TankDrive(-(0.1 * error + 0.9), (0.1 * error + 0.9));
	}
	else{
		TankDrive(0.0f, 0.0f);
		return true;
	}

	return false;
}

void DriveTrain::TankDrive(double leftAxis, double rightAxis)
{
	pRobot->TankDrive(leftAxis, rightAxis);
}

// Equations for encoders = encoder ticks * (2PIr)

int DriveTrain::GetLeftEncoderValue(){
	double data = pLeftFrontMotor->GetPosition();
	double equation = 2.0 * 3.141 * 3.0;

	return data * equation;
}

int DriveTrain::GetRightEncoderValue(){
	double data = pRightFrontMotor->GetPosition();
	double equation = 2.0 * 3.141 * 3.0;

	return data * equation;
}

double DriveTrain::GetRightSpeed(){
	double data = pRightFrontMotor->GetSpeed();
	double equation = 2.0 * 3.141 * 3.0;
	return data * equation;
}

double DriveTrain::GetLeftSpeed(){
	double data = pLeftFrontMotor->GetSpeed();
	double equation = 2.0 * 3.141 * 3.0;
	return data * equation;
}

void DriveTrain::LightLED() {
	pLED1->Set(1);
}


bool DriveTrain::GetSwitchPositionOne() {
	return pDipSwitchOne->Get();
}

bool DriveTrain::GetSwitchPositionTwo() {
	return pDipSwitchTwo->Get();
}

bool DriveTrain::GetSwitchPositionThree() {
	return pDipSwitchThree->Get();
}

bool DriveTrain::GetSwitchPositionFour() {
	return pDipSwitchFour->Get();
}

void DriveTrain::Turn(float speed, float direction)
{
	pRobot->Drive(speed, direction);
}

double DriveTrain::GetGyro(){
	return pGyro->GetAngle();
}

void DriveTrain::Calibrate(){
	pGyro->Calibrate();
}

void DriveTrain::ResetGyro(){
	pGyro->Reset();
}
