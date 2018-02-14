#ifndef _CODETOOLS_HG_
#define _CODETOOLS_HG_
bool togglePressed;
namespace ct {
bool ToggleBool(bool input){
	bool togglePressed = false;
	bool toggleOn = false;
	if(input){
		if(!togglePressed){
			toggleOn = !toggleOn;
			togglePressed = true;
		}
	}else{
		togglePressed = false;
	}
	return toggleOn;
} // togglebool

}
/*
 * this is the alternate code that should be used if the above function does not work properly
typedef enum _tog { true, false } tog;
	tog mode = true;
	bool current, prev;
	prev = current = false;
	// Check the mode toggle button
	current = input;
	if (mode == true) {
		int direction = 1;
		if (current && !prev){ mode = false; }
	}
	else if (mode == false) {
		int direction = -1;
	    if (current && !prev){ mode = true; }
	}
	prev = current;
	return current;
*/

#endif
