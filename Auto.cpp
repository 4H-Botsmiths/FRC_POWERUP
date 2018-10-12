#include "Robot.h"

void Robot::AutonomousInit() {
	/*
	//std::string pos=frc::SmartDashboard::GetString("POSITION", "LEFT");
	std::string obj=frc::SmartDashboard::GetString("SCALE/SWITCH", "SWITCH");
	//std::string dir=frc::SmartDashboard::GetString("GOTO SIDE", "LEFT");
	std::string cmd=frc::SmartDashboard::GetString("CUSTOM", "");
	std::string dir=frc::DriverStation::GetInstance().GetGameSpecificMessage();
	std::string go2=frc::SmartDashboard::GetString("GOTO", "LEFT");
	//frc::SmartDashboard::PutString("AUTOSTUFF", pos+"|"+obj+"|"+dir);
*/
	//frc::SendableChooser<frc::Command*> temp;
	frc::Sendable* temp;

	//std::string val=frc::SmartDashboard::GetValue("POSITION");
	//temp=frc::SmartDashboard::GetData("POSITION");
	temp=a_position.GetSelected();
	//frc::SmartDashboard::PutString("VAR", temp.GetSelected());
	//std::string test=frc::SmartDashboard::GetString("TEST", "NON");

	std::cout << "\n\n\n\n\n\n\n$$#$$[" << temp << "]";

	/*
	if (test == "LF") {
		d_motor_lf.Set(1);
	}
	else if (test == "LR") {
		d_motor_lr.Set(1);
	}
	else if (test == "RF") {
		d_motor_rf.Set(1);
	}
	else if (test == "RR") {
		d_motor_rr.Set(1);
	}
	*/

	//dir="LLL";

	/*
	double dirmult=0;
	if (dir.length() > 0) {
		if ((dir[0] == 'L' && obj == "SWITCH") || (dir[1]== 'L' && obj=="SCALE")) { //scale/switch is selected and on left side, set 'goto-side' as left
			dirmult=-A_SPEED;
		}
		else if ((dir[0] == 'R' && obj == "SWITCH") || (dir[1]== 'R' && obj=="SCALE")) { //scale/switch is selected and on right side, set 'goto-side' as right
			dirmult=A_SPEED;
		}
		else { //switch or scale are not selected
			if (pos == "LEFT") {
				dirmult=-A_SPEED;
			}
			else if (pos == "RIGHT") {
				dirmult=A_SPEED;
			}
		}
	}
	if (dir == "LEFT") { //multiplier to change the dirrectoin depending on feild position AKA mirrored autonomous modes
		dirmult=-A_SPEED;
	}
	else {
		dirmult=A_SPEED;
	}
	s_move(g_solenoid, G_CLOSE); //start all auto modes by closing the grabber
	if (obj == "AUTO ONLY") { //just do the auto line, and nothing else
		if (pos == "LEFT" || pos == "RIGHT") {
			d_move(dirmult, 0, 0, 3);
		}
		else if (pos == "MIDDLE") {
			d_move(0, A_SPEED, 0, 2);
			d_move(dirmult, 0, 0, 2);
			d_move(0, A_SPEED, 0, 1);
		}
	}
	else if (obj == "SWITCH") {
		e_move(E_SPEED, 3);
		if (pos == "LEFT" || pos == "RIGHT") {
			d_move(dirmult, 0, 0, 3);
		}
		else if (pos == "MIDDLE") {
			d_move(0, A_SPEED, 0, 2);
			d_move(dirmult, 0, 0, 1);
			s_move(g_solenoid, G_OPEN);
			d_move(dirmult, 0, 0, 1);
			d_move(0, A_SPEED, 0, 1);
			//d_move(0, A_SPEED, 0, 1);
		}
		s_move(g_solenoid, G_OPEN);
	}
	else if (obj == "SCALE") {
		e_move(E_SPEED, 6);
		if (pos == "LEFT" || pos == "RIGHT") {
			d_move(dirmult*0.75, 0, 0, 5);
		}
		else if (pos == "MIDDLE") {
			d_move(0, A_SPEED, 0, 2);
			d_move(dirmult, 0, 0, 3);
			d_move(0, A_SPEED, 0, 3);
			d_move(0, 0, A_SPEED, 2);
			//d_move(0, A_SPEED, 0, 1);
		}
		s_move(g_solenoid, G_OPEN);
	}
	else if (obj == "VAULT") {
		s_move(g_solenoid, G_OPEN);
		if (pos == "LEFT") {
			d_move(-A_SPEED, 0, 0, 1);
			d_move(0, A_SPEED, 0, 1);
			d_move(A_SPEED, 0, 0, 1);
			d_move(0, -A_SPEED, 0, 1);
			d_move(dirmult, 0, 0, 3);
		}
		if (pos == "RIGHT") {
			d_move(A_SPEED, 0, 0, 1);
			d_move(0, A_SPEED, 0, 3);
			d_move(-A_SPEED, 0, 0, 1);
			d_move(0, -A_SPEED, 0, 3);
			d_move(dirmult, 0, 0, 3);
		}
		if (pos == "MIDDLE") {
			d_move(0, A_SPEED, 0, 1);
			d_move(-A_SPEED, 0, 0, 1);
			d_move(0, -A_SPEED, 0, 1);
			d_move(A_SPEED, 0, 0, 2);
			d_move(0, 1, 0, 3);
		}
	}
	else if (obj == "CUSTOM") {
		//Possible options are: XxYyGgMmEe
		if (cmd.size() != 0) {
			for (char& i : cmd) {
				if (i == 'Y') {
					d_move(0, A_SPEED, 0, A_TIME);
				}
				else if (i == 'y') {
					d_move(0, -A_SPEED, 0, A_TIME);
				}
				else if (i == 'x') {
					d_move(-A_SPEED, 0, 0, A_TIME);
				}
				else if (i == 'X') {
					d_move(A_SPEED, 0, 0, A_TIME);
				}
				else if (i == 'E') {
					e_move(E_SPEED, A_TIME);
				}
				else if (i == 'e') {
					e_move(-E_SPEED, A_TIME);

				}
				else if (i == 'G') {
					s_move(g_solenoid, G_CLOSE);
				}
				else if (i == 'g') {
					s_move(g_solenoid, G_OPEN);
				}
				else if (i == 'M') {
					m_move(M_SPEED, A_TIME);
				}
				else if (i == 'm') {
					m_move(-M_SPEED, A_TIME);
				}
			}
		}
	}
	*/
	/*
	if ((dir[0] == 'L' && pos == "LEFT") || (dir[0] == 'R' && pos == "RIGHT")) {
		d_move(0, -1, 0, 1.5);
	}
	else {
		e_move(1, 2);
		e_move(-1, 2);
		d_move(0, -1, 30, 2);
	}
	*/
	d_move(0, -1, 0, 1.5);
}
