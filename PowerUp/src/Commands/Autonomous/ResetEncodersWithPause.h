#ifndef SRC_COMMANDS_RESETENCODERSWITHPAUSE_H_
#define SRC_COMMANDS_RESETENCODERSWITHPAUSE_H_

#include <Timer.h>
#include <WPILib.h>
#include "../../CommandBase.h"


class ResetEncodersWithPause : public CommandBase
{
public:
	ResetEncodersWithPause(double timeToPauseInSeconds);
	~ResetEncodersWithPause(void);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	ResetEncodersWithPause();	// Private, so can't be called

	double m_timeToPauseInSeconds;
	Timer* pTimer;
};

#endif /* SRC_COMMANDS_RESETENCODERSWITHPAUSE_H_ */
