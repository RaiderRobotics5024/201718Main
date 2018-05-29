
#pragma once
#include <CommandBase.hpp>
#include <WPILib.h>

class CVControl : public frc::Command {
public:
	CVControl();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	std::shared_ptr<NetworkTable> table;
	bool lock = true;
};

