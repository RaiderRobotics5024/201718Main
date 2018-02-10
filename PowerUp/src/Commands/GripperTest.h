#ifndef _GRIPPER_TEST_HG_
#define _GRIPPER_TEST_HG_

#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */

class GripperTest: public CommandBase
{
public:
	GripperTest();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif
