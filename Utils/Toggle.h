/*
 * WORK OF FRC TEAM 4309
 *
 * Adds onto the xbox class to allow for simple button toggles
 *
 * This assorted collection of characters contains no restrictions and can be used by all
 */

#pragma once

#include <XboxController.h>

namespace frc {

class Toggle {
public:
	bool FirstPress(bool &x) {
		PressedLast=PressedNow;
		PressedNow=x;
		if (x && !PressedLast) {
			return true;
		}
		else {
			return false;
		}
	}
private:
	bool PressedLast=false;  //bool state last check
	bool PressedNow=false;   //bool state this check
};

}
