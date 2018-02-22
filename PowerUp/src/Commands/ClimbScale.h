#ifndef SRC_COMMANDS_CLIMBSCALE_H_
#define SRC_COMMANDS_CLIMBSCALE_H_

#include <WPILib.h>
#include "../CommandBase.h"

class ClimbScale : public CommandBase
{
public:
	ClimbScale();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

};

#endif /* SRC_COMMANDS_CLIMBSCALE_H_ */
