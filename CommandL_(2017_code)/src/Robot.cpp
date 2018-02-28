#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "Commands/JoystickDrive.h"
#include "Commands/AutoSequenceOne.h"
#include "Commands/AutoSequenceTwo.h"
#include "Commands/AutoSequenceThree.h"
#include "Commands/AutoSequenceFour.h"
#include "Commands/AutoSequenceFive.h"
#include "Commands/AutoSequenceSix.h"
#include "Commands/AutoSequenceSeven.h"
#include "CommandBase.h"

class Robot: public IterativeRobot
{
private:
	Command* pAutonomousCommand;
	SendableChooser autoChooser;

	void RobotInit()
	{
		CommandBase::init();

		// instantiate the command used for the autonomous period


		autoChooser.AddObject("Spy Bot Position", new AutoSequenceOne());
		autoChooser.AddObject("Low Bar, encoders", new AutoSequenceTwo());
		autoChooser.AddObject("Just Chill", new AutoSequenceThree());
		autoChooser.AddObject("Shoot Only", new AutoSequenceFour());
		autoChooser.AddDefault("Just charge", new AutoSequenceFive());
		autoChooser.AddObject("Low Bar, no shoot", new AutoSequenceSix());
		autoChooser.AddObject("Low Bar, ultra", new AutoSequenceSeven());

		SmartDashboard::PutData("Auto Mode", &autoChooser);


		if(CommandBase::pDriveTrain->GetSwitchPositionOne() == true && CommandBase::pDriveTrain->GetSwitchPositionTwo() == false) {
			pAutonomousCommand = new AutoSequenceOne();
			CommandBase::pDriveTrain->LightLED();
		}

		if(CommandBase::pDriveTrain->GetSwitchPositionOne() == false && CommandBase::pDriveTrain->GetSwitchPositionTwo() == true) {
			pAutonomousCommand = new AutoSequenceTwo();
		}
		Log();
	}

	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{

		pAutonomousCommand = (Command *)autoChooser.GetSelected();

		//CommandBase::pDriveTrain->ResetGyro();
		if (pAutonomousCommand != NULL)
			pAutonomousCommand->Start();
	}

	void AutonomousPeriodic()
	{
		Scheduler::GetInstance()->Run();
		Log();
	}

	void TeleopInit()
	{
		// This makes sure that the autonomous stops running when teleop starts running
		if (pAutonomousCommand != NULL)
			pAutonomousCommand->Cancel();
	}

	void TeleopPeriodic()
	{
		Scheduler::GetInstance()->Run();
		Log();
	}

	void TestPeriodic()
	{

	}

	void Log()
	{
		SmartDashboard::PutNumber("Gyro", CommandBase::pDriveTrain->GetGyro());
		SmartDashboard::PutNumber("Front Ultra_Port5", CommandBase::pBIOS->GetUltraAt(ULTRASONIC_FRONT_ANIPORT));
		SmartDashboard::PutNumber("Front Ultra_Port2", CommandBase::pBIOS->GetUltraAt(2));

		SmartDashboard::PutNumber("Encoder Distance", CommandBase::pDriveTrain->GetRightEncoderValue());

		// Added in St. Louis April 28, 2016
		int RightEncVal = CommandBase::pDriveTrain->GetRightEncoderValue();
		int LeftEncVal = CommandBase::pDriveTrain->GetLeftEncoderValue();
		float AvgEncVal = (static_cast<float>(RightEncVal) + static_cast<float>(LeftEncVal))/2.0f;

		SmartDashboard::PutNumber("R.Enc Dist:", RightEncVal);
		SmartDashboard::PutNumber("L.Enc Dist:", LeftEncVal);
		SmartDashboard::PutNumber("Avg.Enc Dist:", AvgEncVal);

		SmartDashboard::PutString("Spy Bot Position", "Auto_1");
		SmartDashboard::PutString("Low Bar, encoders", "Auto_2");
		SmartDashboard::PutString("Low Bar, no shoot", "Auto_2");
		SmartDashboard::PutString("Just Chill", "Auto_3");
		SmartDashboard::PutString("Just Shoot", "Auto_4");
		SmartDashboard::PutString("Just Charge", "Auto_5");
		SmartDashboard::PutString("Low Bar, ultra", "Auto_7");



/*
		SmartDashboard::PutNumber("Port 0", CommandBase::pBIOS->GetUltraAt(0));
		SmartDashboard::PutNumber("Port 1", CommandBase::pBIOS->GetUltraAt(1));
		SmartDashboard::PutNumber("Port 2", CommandBase::pBIOS->GetUltraAt(2));
		SmartDashboard::PutNumber("Port 3", CommandBase::pBIOS->GetUltraAt(3));
		SmartDashboard::PutNumber("Port 4", CommandBase::pBIOS->GetUltraAt(4));
		SmartDashboard::PutNumber("Port 5", CommandBase::pBIOS->GetUltraAt(5));
		SmartDashboard::PutNumber("Port 6", CommandBase::pBIOS->GetUltraAt(6));
		SmartDashboard::PutNumber("Port 7", CommandBase::pBIOS->GetUltraAt(7));

*/
		//CameraServer::GetInstance()->SetQuality(50);
		//CameraServer::GetInstance()->StartAutomaticCapture("cam0");

	}
};

START_ROBOT_CLASS(Robot);

