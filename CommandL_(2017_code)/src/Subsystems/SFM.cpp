#include "SFM.h"
#include "Commands/Subsystem.h"
#include "../RobotMap.h"
#include "Commands/DoTheThing.h"

SFM::SFM() :
		Subsystem("SFM")
{
	//solenoid forcing module
	compressor = new Compressor(0);
	sfm = new DoubleSolenoid(6, 7);
	pLimitSwitch = new DigitalInput(LIMIT_SWITCH_2);
	sfm->Set(DoubleSolenoid::kOff);
	compressor->Stop(); //default off
}

void SFM::InitDefaultCommand()
{
	SetDefaultCommand(new DoTheThing());
}

void SFM::StopCompressor(){
	compressor->Stop();
}

void SFM::StartCompressor(){
	compressor ->Start();
}

bool SFM::IsSwitchSet(){
	return pLimitSwitch->Get();
}

void SFM::SetForward()
{
	sfm->Set(DoubleSolenoid::kForward);
}

void SFM::SetReverse()
{
	sfm->Set(DoubleSolenoid::kReverse);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
