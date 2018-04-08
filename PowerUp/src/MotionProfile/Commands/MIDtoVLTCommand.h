#ifndef _MIDTOVLTCOMMAND_HG_
#define _MIDTOVLTCOMMAND_HG_

#include <Timer.h>
#include <WPILib.h>
#include "../Profiles/MIDtoVLTProfile.h"
#include "../../CommandBase.h"

/**
 *
 */
class MIDtoVLTCommand : public CommandBase
{
public:
	MIDtoVLTCommand(Height::Type height = Height::NONE);
	~MIDtoVLTCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	MIDtoVLTProfile* pMotionProfiler;
	Height::Type htHeight = Height::NONE;
	Timer* pTimer;
};

#endif
