#ifndef SFM_H
#define SFM_H

#include "Commands/Subsystem.h"

#include "WPILib.h"

class SFM: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	DoubleSolenoid* sfm;

	DigitalInput* pLimitSwitch;
public:
	Compressor* compressor;
	SFM();

	void InitDefaultCommand();
	void SetForward();
	void SetReverse();
	bool IsSwitchSet();
	void StartCompressor();
	void StopCompressor();
};

#endif
