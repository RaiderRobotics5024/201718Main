#include "BIOS.h"
#include "Commands/RumbleInRange.h"
#include "../RobotMap.h"

BIOS::BIOS() :
Subsystem("BIOS")
{
	pCollectorMotor = new CANTalon(TALON_COLLECTOR);
	pShooterMotorRight = new CANTalon(TALON_RIGHT_SHOOTER);
	pShooterMotorLeft = new CANTalon(TALON_LEFT_SHOOTER);

	pShooterMotorLeft->SetInverted(true);

	prefs = Preferences::GetInstance();
	fShootSpeed = prefs->GetFloat("BIOS_ShootSpeed", 0.0f);
	fIntakeSpeed = prefs->GetFloat("BIOS_IntakeSpeed", 0.0f);
	fKickerSpeed = prefs->GetFloat("BIOS_KickerSpeed", 0.0f);
	//fRegressionSpeed = 0.0;

	limitSwitch = new DigitalInput(LIMIT_SWITCH_1);
	counter = new Counter(limitSwitch);

	frontUltra_p5 = new AnalogInput(ULTRASONIC_FRONT_ANIPORT);

	frontUltra_p0 = new AnalogInput(0);
	frontUltra_p1 = new AnalogInput(1);
	frontUltra_p2 = new AnalogInput(2);
	frontUltra_p3 = new AnalogInput(3);
	frontUltra_p4 = new AnalogInput(4);
	frontUltra_p6 = new AnalogInput(6);
	frontUltra_p7 = new AnalogInput(7);


	//frontUltra->SetSampleRate(100);

	pTimer = new Timer;
}


void BIOS::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new RumbleInRange());
}

void BIOS::Intake(float speed)
{
	pCollectorMotor->Set(-speed);
}

void BIOS::Shoot(float speed)
{
	SmartDashboard::PutNumber("ShootSpeed", speed);
	pShooterMotorRight->Set(speed);
	pShooterMotorLeft->Set(speed);
}

void BIOS::RumbleWhenRange(double target, double variance){
	if(abs(GetUltraAt(ULTRASONIC_FRONT_ANIPORT) - target) <= variance){
		CommandBase::pOI->GetDrive()->SetRumble(Joystick::RumbleType::kLeftRumble, 1.0f);
		CommandBase::pOI->GetMech()->SetRumble(Joystick::RumbleType::kLeftRumble, 1.0f);
	}else{
		CommandBase::pOI->GetDrive()->SetRumble(Joystick::RumbleType::kLeftRumble, 0.0f);
		CommandBase::pOI->GetMech()->SetRumble(Joystick::RumbleType::kLeftRumble, 0.0f);
	}
}

void BIOS::StopIntake()
{
	pCollectorMotor->Set(0);
}

void BIOS::StopShoot()
{
	pShooterMotorRight->Set(0);
	pShooterMotorLeft->Set(0);
}

void BIOS::LowGoal()
{
	pCollectorMotor->Set(prefs->GetFloat("BIOS_LowGoalSpeed", 0.75f));
}

void BIOS::StartTimer()
{
	pTimer->Start();
}

double BIOS::GetCurrentTime()
{
	return pTimer->Get();
}

void BIOS::StopTimer()
{
	pTimer->Stop();
	pTimer->Reset();
}


float BIOS::GetShootSpeed()
{
	fShootSpeed = prefs->GetFloat("BIOS_ShootSpeed", 0.6f);
	return fShootSpeed;
}

float BIOS::GetShootSpeed(double displacement)
{
	//displacement, speed
	//not global so that you don't have to reload code everytime
	std::map<int, double> speedMap = {
			{ 4, Preferences::GetInstance()->GetDouble("BIOS_SpeedAt_4", 1.0f)},
			{ 6, Preferences::GetInstance()->GetDouble("BIOS_SpeedAt_6", 1.0f)},
			{ 8, Preferences::GetInstance()->GetDouble("BIOS_SpeedAt_8", 1.0f)},
			{ 10, Preferences::GetInstance()->GetDouble("BIOS_SpeedAt_10", 1.0f)},
			{ 101, Preferences::GetInstance()->GetDouble("Auto1_ShootSpeed", 0.9f)},
			{ 102, Preferences::GetInstance()->GetDouble("Auto2_ShootSpeed", 0.95f)},
			{ 104, Preferences::GetInstance()->GetDouble("Auto4_ShootSpeed", 0.95f)},
			{ 107, Preferences::GetInstance()->GetDouble("Auto7_ShootSpeed", 1.0f)},
	};

	fShootSpeed = speedMap[displacement];
	return fShootSpeed;
}

float BIOS::GetIntakeSpeed()
{
	fIntakeSpeed = prefs->GetFloat("BIOS_IntakeSpeed", 0.5f);
	return fIntakeSpeed;
}

float BIOS::GetKickerSpeed(){
	fKickerSpeed = prefs->GetFloat("BIOS_KickerSpeed", 1.0f);
	return fKickerSpeed;
}

bool BIOS::IsSwitchSet() {
	return limitSwitch->Get();
	//return counter->Get() > 0;
}

void BIOS::InitializeCounter() {
	counter->Reset();
}

double BIOS::GetTempFromPref(){
	return prefs->GetFloat("Ultra_Temperature", 20.0f); //assume 25 degrees
}

double BIOS::GetUltraAt(int port){
	double Vm = 0; //analog voltage from sensor
	double Tc = GetTempFromPref(); //temperature, human input
	double Vcc = VCC; //5V supply
	int rawAD = 0;

	switch(port){
	case 0:
		Vm = frontUltra_p0->GetAverageVoltage();
		rawAD = frontUltra_p0->GetValue();
		break;
	case 1:
		Vm = frontUltra_p1->GetAverageVoltage();
		rawAD = frontUltra_p1->GetValue();
		break;
	case 2:
		Vm = frontUltra_p2->GetAverageVoltage();
		rawAD = frontUltra_p2->GetValue();
		break;
	case 3:
		Vm = frontUltra_p3->GetAverageVoltage();
		rawAD = frontUltra_p3->GetValue();
		break;
	case 4:
		Vm = frontUltra_p4->GetAverageVoltage();
		rawAD = frontUltra_p4->GetValue();
		break;
	case 5:
		Vm = frontUltra_p5->GetAverageVoltage();
		rawAD = frontUltra_p5->GetValue();
		break;
	case 6:
		Vm = frontUltra_p6->GetAverageVoltage();
		rawAD = frontUltra_p6->GetValue();
		break;
	case 7:
		Vm = frontUltra_p7->GetAverageVoltage();
		rawAD = frontUltra_p7->GetValue();
		break;
	default:
		Vm = 9999.9; //impossible value
		break;
	}
	//SmartDashboard::PutNumber("Voltage Reading", Vm);
	//SmartDashboard::PutNumber("Raw Value", rawAD);
	//return rawReading * ULTRASONIC_READING_TO_INCH / ULTRASONIC_SCALEFACTOR; //empirical
	return (Vm * 107.609 + 64.384)/100;
	//return Vm * 1.086 + 0.606; //3 data point regression
	//return (Vm/(Vcc/1024) * (58 * pow(10,-6)) * (20.05 * pow((Tc + 273.15), 0.5)/2)); //return value in meteres with temp compensation
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
