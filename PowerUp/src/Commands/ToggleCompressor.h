#ifndef _COMPRESSOR_TOGGLE_HG_
#define _COMPRESSOR_TOGGLE_HG_

#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */
#include <Commands/Command.h>

class ToggleCompressor : public frc::Command {
public:
	ToggleCompressor();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif
