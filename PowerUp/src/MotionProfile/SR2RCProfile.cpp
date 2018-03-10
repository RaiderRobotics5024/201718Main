#include "SR2RCProfile.h"

/**
 *
 */
SR2RCProfile::SR2RCProfile(TalonSRX & talon) : _talon(talon), _notifer(&SR2RCProfile::PeriodicTask, this)
{
	_pos = 0, _vel = 0, _heading = 0, _state = 0;
	_loopTimeout = 30;
	_bStart = false;
	_setValue = SetValueMotionProfile::Disable;

	_talon.ChangeMotionControlFramePeriod(5);

	_notifer.StartPeriodic(0.005);

	return;
}

/**
 *
 */
void SR2RCProfile::PeriodicTask()
{
	_talon.ProcessMotionProfileBuffer();
}

/**
 *
 */
void SR2RCProfile::reset()
{
	_talon.ClearMotionProfileTrajectories();
	_setValue = SetValueMotionProfile::Disable;
	_state = 0;
	_loopTimeout = -1;
	_bStart = false;
}

/**
 * Called every loop.
 */
void SR2RCProfile::control()
{
	if (_loopTimeout < 0)
	{
		/* do nothing, timeout is disabled */
	} else
	{
		if (_loopTimeout == 0)
		{
			Instrumentation::OnNoProgress();
		}
		else
		{
			--_loopTimeout;
		}
	}

	if (_talon.GetControlMode() != ControlMode::MotionProfile)
	{
		_state = 0;
		_loopTimeout = -1;
	}
	else
	{
		switch (_state)
		{
			case 0: /* wait for application to tell us to start an MP */
				if (_bStart)
				{
					_bStart = false;

					_setValue = SetValueMotionProfile::Disable;
					startFilling();

					/*
					 * MP is being sent to CAN bus, wait a small amount of time
					 */
					_state = 1;
					_loopTimeout = kNumLoopsTimeout;
				}
				break;
			case 1:
				if (_status.btmBufferCnt > kMinPointsInTalon)
				{
					_setValue = SetValueMotionProfile::Enable;
					_state = 2;
					_loopTimeout = kNumLoopsTimeout;
				}
				break;
			case 2: /* check the status of the MP */
				if (_status.isUnderrun == false)
				{
					_loopTimeout = kNumLoopsTimeout;
				}

				if (_status.activePointValid && _status.isLast)
				{
					_setValue = SetValueMotionProfile::Hold;
					_state = 0;
					_loopTimeout = -1;
				}
				break;
		}

		/* Get the motion profile status every loop */
		_talon.GetMotionProfileStatus(_status);
		_heading = _talon.GetActiveTrajectoryHeading();
		_pos = _talon.GetActiveTrajectoryPosition();
		_vel = _talon.GetActiveTrajectoryVelocity();

		/* printfs and/or logging */
		Instrumentation::Process(_status, _pos, _vel, _heading);
	}
}

/**
 *
 */
TrajectoryDuration SR2RCProfile::GetTrajectoryDuration(int durationMs)
{
	/* lookup and return valid value */
	switch (durationMs)
	{
		case 0:		return TrajectoryDuration_0ms;
		case 5:		return TrajectoryDuration_5ms;
		case 10: 	return TrajectoryDuration_10ms;
		case 20: 	return TrajectoryDuration_20ms;
		case 30: 	return TrajectoryDuration_30ms;
		case 40: 	return TrajectoryDuration_40ms;
		case 50: 	return TrajectoryDuration_50ms;
		case 100: 	return TrajectoryDuration_100ms;
	}
	printf("Trajectory Duration not supported - use configMotionProfileTrajectoryPeriod instead\n");

	return TrajectoryDuration_100ms;
}

/**
 *
 */
void SR2RCProfile::startFilling()
{
	startFilling(kSR2RCProfile, kSR2RCProfileSz);
}

/**
 *
 */
void SR2RCProfile::startFilling(const double profile[][3], int totalCnt)
{
	TrajectoryPoint point;

	if (_status.hasUnderrun) {
		Instrumentation::OnUnderrun();
		_talon.ClearMotionProfileHasUnderrun(TIMEOUT_MS);
	}

	_talon.ClearMotionProfileTrajectories();

	_talon.ConfigMotionProfileTrajectoryPeriod(BASE_TRAJECTORY_PERIOD_MS, TIMEOUT_MS);

	for (int i = 0; i < totalCnt; ++i)
	{
		double positionRot = profile[i][0];
		double velocityRPM = profile[i][1];

		point.position = positionRot * TICKS_PER_REVOLUTION; //Convert Revolutions to Units
		point.velocity = velocityRPM * TICKS_PER_REVOLUTION / 600.0; //Convert RPM to Units/100ms
		point.headingDeg = 0; /* future feature - not used in this example*/
		point.profileSlotSelect0 = 0; /* which set of gains would you like to use [0,3]? */
		point.profileSlotSelect1 = 0; /* future feature  - not used in this example - cascaded PID [0,1], leave zero */
		point.timeDur = GetTrajectoryDuration((int) profile[i][2]);
		point.zeroPos = false;
		if (i == 0)
			point.zeroPos = true; /* set this to true on the first point */

		point.isLastPoint = false;
		if ((i + 1) == totalCnt)
			point.isLastPoint = true; /* set this to true on the last point  */

		_talon.PushMotionProfileTrajectory(point);
	}
}

/**
 *
 */
void SR2RCProfile::start()
{
	_bStart = true;
}

/**
 *
 */
SetValueMotionProfile SR2RCProfile::getSetValue()
{
	return _setValue;
}
