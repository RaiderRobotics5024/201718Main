#ifndef _PY1TORCPROFILE_HG_
#define _PY1TORCPROFILE_HG_

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "../Instrumentation.h"

#include "../Paths/PY1toRCPath.h"

/**
 *
 */
class PY1toRCProfile
{
public:
	PY1toRCProfile(can::WPI_TalonSRX & leftTalon, can::WPI_TalonSRX & rightTalon);
	void control();
	SetValueMotionProfile getSetValue();
	TrajectoryDuration GetTrajectoryDuration(int durationMs);
	void PeriodicTask();
	void reset();
	void start();
	void startFilling();
	void startFilling(const double profileLeft[][3], const double profileRight[][3], int totalCnt);

private:
	MotionProfileStatus _status;
	double _pos = 0, _vel = 0, _heading = 0;
	TalonSRX & _talonLeft;
	TalonSRX & _talonRight;
	int _state = 0;
	int _loopTimeout = 30;
	bool _bStart = false;
	SetValueMotionProfile _setValue;
	static const int kMinPointsInTalon = 5;
	static const int kNumLoopsTimeout = 10;
	Notifier _notifer;
};

#endif
