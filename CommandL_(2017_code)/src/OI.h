#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "Triggers/XBoxTrigger.h"
#include "Triggers/XBoxPOV.h"

class OI
{
private:

public:
	OI();
	Joystick* GetDrive();
	Joystick* GetMech();

	Joystick* xbox_drive; //drive xbox
	Joystick* xbox_mech; //mech xbox

	JoystickButton* xbox_drive_button_A;
	JoystickButton* xbox_drive_button_B;

	XBoxTrigger* xbox_drive_trigger_L;
	XBoxTrigger* xbox_drive_trigger_R;

	JoystickButton* xbox_mech_button_A;
	JoystickButton* xbox_mech_button_B;
	JoystickButton* xbox_mech_button_X;
	JoystickButton* xbox_mech_button_Y;
	JoystickButton* xbox_mech_button_Back;
	JoystickButton* xbox_mech_button_Start;

	XBoxPOV* xbox_mech_POV_up;
	XBoxPOV* xbox_mech_POV_down;




};

#endif
