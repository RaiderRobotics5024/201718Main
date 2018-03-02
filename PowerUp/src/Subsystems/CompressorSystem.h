#ifndef _COMPRESSOR_HG_
#define _COMPRESSOR_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "../RobotMap.h"

/**
 *
 */
class CompressorSystem : public frc::Subsystem
{

public:
	CompressorSystem();
	~CompressorSystem();
	void InitDefaultCommand() override;

	void On(void);
	void Off(void);

private:
	Compressor* pCompressor;
};

#endif
