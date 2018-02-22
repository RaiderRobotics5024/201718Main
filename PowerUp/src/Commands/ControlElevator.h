#ifndef SRC_COMMANDS_CONTROLELEVATOR_H_
#define SRC_COMMANDS_CONTROLELEVATOR_H_

#include <WPILib.h>
#include "../CommandBase.h"

class ControlElevator : public CommandBase
{
public:
	ControlElevator();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif /* SRC_COMMANDS_CONTROLELEVATOR_H_ */
