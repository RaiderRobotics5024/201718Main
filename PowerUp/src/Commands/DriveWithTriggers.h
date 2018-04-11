#ifndef _DRIVEWITHTRIGGERS_HG_
#define _DRIVEWITHTRIGGERS_HG_

#include <WPILib.h>
#include "../CommandBase.h"



class DriveWithTriggers: public CommandBase
{
public:
	DriveWithTriggers();
	~DriveWithTriggers();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif
