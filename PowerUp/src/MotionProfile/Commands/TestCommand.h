#ifndef _TESTCOMMAND_HG_
#define _TESTCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/TestProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class TestCommand : public CommandBase
{
public:
	TestCommand(Height::Type height = Height::NONE);
	~TestCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	TestProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
