#ifndef _SRTORCCOMMAND_HG_
#define _SRTORCCOMMAND_HG_

#include <WPILib.h>
#include "../../CommandBase.h"
#include "../SRtoRCProfile.h"

/**
 *
 */
class SRtoRCCommand : public CommandBase
{
public:
	SRtoRCCommand();
	~SRtoRCCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	SRtoRCProfile* pMotionProfiler;
};

#endif
