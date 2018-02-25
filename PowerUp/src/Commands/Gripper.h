#ifndef SRC_COMMANDS_GRIPPER_H_
#define SRC_COMMANDS_GRIPPER_H_

#include <WPILib.h>
#include "../CommandBase.h"

class Gripper : public CommandBase
{
public:
	Gripper();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

};



#endif /* SRC_COMMANDS_GRIPPER_H_ */
