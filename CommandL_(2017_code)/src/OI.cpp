#include "OI.h"
#include "RobotMap.h"

#include "Commands/ExtendSFM.h"
#include "Commands/RetractSFM.h"
#include "Commands/TimedShoot.h"
#include "Commands/Intake.h"
#include "Commands/ShootLowGoal.h"
#include "Commands/TimedShoot.h"
#include "Commands/RetractSFM.h"
#include "Commands/ExtendSFM.h"
#include "Commands/ReverseDrive.h"
#include "Commands/RotateWithGyro.h"
#include "Commands/ToggleCompressor.h"

OI::OI()
{
	//NOTE: all triggers are handled in ExecuteJoystick command

	// Process operator interface input here.
	xbox_drive = new Joystick(XBOX_DRIVE_PORT);
	xbox_mech = new Joystick(XBOX_MECH_PORT);

	//xbox_drive_right_trigger = new JoystickButton(xbox_drive, XBOX_R_TRIGGER);
	//xbox_drive_left_trigger = new JoystickButton(xbox_drive, XBOX_L_TRIGGER);
	xbox_drive_button_A = new JoystickButton(xbox_drive, XBOX_BTN_A);
	xbox_drive_button_B = new JoystickButton(xbox_drive, XBOX_BTN_B);

	//xbox_drive_right_trigger->WhenActive(new RetractSFM());
	//xbox_drive_left_trigger->WhenActive(new ExtendSFM());
	xbox_drive_button_A->WhenPressed(new ReverseDrive());
	xbox_drive_button_B->WhenPressed(new RotateWithGyro());

	xbox_mech_button_A = new JoystickButton(xbox_mech, XBOX_BTN_A);
	xbox_mech_button_B = new JoystickButton(xbox_mech, XBOX_BTN_B);
	xbox_mech_button_X = new JoystickButton(xbox_mech, XBOX_BTN_X);
	xbox_mech_button_Y = new JoystickButton(xbox_mech, XBOX_BTN_Y);
	xbox_mech_button_Start = new JoystickButton(xbox_mech, XBOX_BTN_START);
	xbox_mech_button_Back = new JoystickButton(xbox_mech, XBOX_BTN_BACK);

	xbox_mech_POV_up = new XBoxPOV(xbox_mech, XBOX_POV_UP);
	xbox_mech_POV_down = new XBoxPOV(xbox_mech, XBOX_POV_DOWN);
	xbox_mech_POV_up->WhenActive(new ShootLowGoal());
	xbox_mech_POV_down->WhenActive(new Intake());

	xbox_drive_trigger_L = new XBoxTrigger(xbox_drive, XBOX_L_TRIGGER);
	xbox_drive_trigger_R = new XBoxTrigger(xbox_drive, XBOX_R_TRIGGER);
	xbox_drive_trigger_R->WhenActive(new ExtendSFM());
	xbox_drive_trigger_L->WhenActive(new RetractSFM());

	xbox_mech_button_A->WhenPressed(new TimedShoot(4));
	xbox_mech_button_B->WhenPressed(new TimedShoot(6));
	xbox_mech_button_Y->WhenPressed(new TimedShoot(8));
	xbox_mech_button_X->WhenPressed(new TimedShoot(10));
	xbox_mech_button_Start->WhenPressed(new ToggleCompressor(true));
	xbox_mech_button_Back->WhenPressed(new ToggleCompressor(false));


}

Joystick* OI::GetDrive(){
	return xbox_drive;
}

Joystick* OI::GetMech(){
	return xbox_mech;
}

/* Notes for the XBox controller:
        Button A: 1
        Button B: 2
        Button X: 3
        Button Y: 4
        Button LB: 5
        Button RB: 6
        Button LT: Range 0 to 1.000 (stick.GetTrigger())
        Button RT: Range 0 to -1.000 (stick.GetTrigger())
        Button Back: 7
        Button Start: 8
        Left Axis press: 9
                         X-Axis: -1.000 to 1.000 (stick.GetX())
                         Y-Axis: -1.000 to 1.000 (stick.GetY())
        Right Axis press: 10
                         X-Axis: -1.000 to 1.000 (stick.GetTwist())
                         Y-Axis:
 */
