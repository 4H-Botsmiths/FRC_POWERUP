/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

/*returns 0 if value is inside deadzone, else scales naturally so you can still go to 100%
 * Has 2 overloads, first has 1 input value assuming default deadzone
 * second has 1 input for value and 1 for deadzone input
 */
double Robot::x_zone(double input, double range) {
	double temp = 0.0;
	if (input <= range && input >= -range) {
			return 0.0;
	}
	else {
		if (input > range) {
			temp = input - range - ((input / 100) * D_OFFSET);
		}
		else if (input < range) {
			temp = input + range + ((input / 100) * D_OFFSET);
		}
	}
	return temp;
}
double Robot::x_zone(double input) {
	double temp = 0.0;
	if (input <= D_OFFSET && input >= -D_OFFSET) {
			return 0.0;
	}
	else {
		if (input > D_OFFSET) {
			temp = input - D_OFFSET - ((input / 100) * D_OFFSET);
		}
		else if (input < D_OFFSET) {
			temp = input + D_OFFSET + ((input / 100) * D_OFFSET);
		}
	}
	return temp;
}

double Robot::x_slow(double input) {
	if (x_controller_r.GetBumper(frc::GenericHID::kLeftHand)) {
		return input*X_SLOW;
	}
	return input;
}

/*
 * Checks to see if the state of grabber has changed, and update accordingly
 * Uses seperate buttons as opposed to a toggle as getbutton() returns true continually, while we need it to do only once
 */
void Robot::s_move(frc::DoubleSolenoid &s, bool f) {
	if (f) {
		s.Set(frc::DoubleSolenoid::Value::kForward);
	}
	else {
		s.Set(frc::DoubleSolenoid::Value::kReverse);
	}
}

void Robot::e_move(double d, double t) {
	frc::Timer timer;
	timer.Start();
	e_motor.Set(d);
	frc::Wait(t);
	e_motor.Set(0);
}

void Robot::m_move(double d, double t) {
	frc::Timer timer;
	timer.Start();
	g_motor.Set(1);
	frc::Wait(t);
	g_motor.Set(0);
}

void Robot::d_move(double x, double y, double r, double t) {
	frc::Timer timer;
	timer.Start();
	while (!timer.HasPeriodPassed(t)) {
		d_train.DriveCartesian(x, y, r);
	}
}
/*
 * Called first, starts important robot features
 */
void Robot::RobotInit() {
	CameraServer::GetInstance()->StartAutomaticCapture(); //initializes camera server

	a_position.AddDefault("LEFT", &a_null);
	a_position.AddObject("MIDDLE", &a_null);
	a_position.AddObject("RIGHT", &a_null);
	frc::SmartDashboard::PutData("POSITION", &a_position);

	a_goto.AddDefault("LEFT", &a_null);
	a_goto.AddObject("RIGHT", &a_null);
	frc::SmartDashboard::PutData("GOTO SIDE", &a_goto);

	a_objective.AddDefault("SWITCH", &a_null);
	a_objective.AddObject("SCALE", &a_null);
	a_objective.AddObject("VAULT", &a_null);
	a_objective.AddObject("NOTHING", &a_null);
	a_objective.AddObject("AUTO ONLY", &a_null);
	a_objective.AddObject("CUSTOM", &a_null);
	frc::SmartDashboard::PutData("OBJECTIVE", &a_objective);

	a_test.AddDefault("LF", &a_null);
	a_test.AddObject("LR", &a_null);
	a_test.AddObject("RF", &a_null);
	a_test.AddObject("RR", &a_null);
	frc::SmartDashboard::PutData("TEST", &a_test);
}
void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Cancel();
		m_autonomousCommand = nullptr;
	}
}

void Robot::TeleopPeriodic() {
	d_train.DriveCartesian(
			x_zone(x_controller_l.GetX(frc::GenericHID::kLeftHand)),
			x_slow(x_zone(x_controller_l.GetY(frc::GenericHID::kLeftHand))),
			x_slow(x_zone(x_controller_l.GetX(frc::GenericHID::kRightHand))));
	e_motor.Set(x_zone(x_controller_r.GetY(frc::GenericHID::kLeftHand)));
	g_motor.Set(x_zone(x_controller_r.GetY(frc::GenericHID::kRightHand)));
	if (x_controller_r.GetAButton()) {
		s_move(g_solenoid, true);
	}
	else if (x_controller_r.GetBButton()) {
		s_move(g_solenoid, false);
	}
	if (x_controller_r.GetXButton()) {
		s_move(e_solenoid, true);
	}
	else if (x_controller_r.GetYButton()) {
		s_move(e_solenoid, false);
	}
	frc::SmartDashboard::PutNumber("WHEEL", d_motor_lf.Get());
}

START_ROBOT_CLASS(Robot);
