#ifndef _CODETOOLS_HG_
#define _CODETOOLS_HG_
bool togglePressed;
namespace ct {

/*
 *
 * INSTRUCTIONS:
 * to call the following function, do the following;
 *
 * static bool toggleOn;
 * static bool togglePressed;
 *
 * output = toggle(<put xbox button here (ex. GetBButton())>, &toggleOn, &togglePressed);
 *
 * ask Evan Pratten for help if you don't understand.
 *
 */
bool toggle(bool input, bool *toggleOn, bool *togglePressed){
	if(input){
			if(!(*togglePressed)){
				*toggleOn = !(*toggleOn);
				*togglePressed = true;
			}
		}else{
			*togglePressed = false;
		}
		return *toggleOn;
}

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
