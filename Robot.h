#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TimedRobot.h>
#include <Drive/MecanumDrive.h>
#include "WPILib.h"

#include <iostream>

#include <Spark.h>
#include <Talon.h>

#include <Timer.h>

#include <DoubleSolenoid.h>

#include <XboxController.h>

#include <Compressor.h>

#include "Commands/ExampleCommand.h"
	#include "Commands/MyAutoCommand.h"

//Offset for deadzone on controllers
#define D_OFFSET 0.10

//values for opening and closing the grabber

#define G_CLOSE true
#define G_OPEN false

#define A_SPEED 0.75
#define A_TIME 1.0

#define E_SPEED 0.8

#define M_SPEED 1.0

#define X_SLOW 0.5

class Robot : public frc::TimedRobot {
public:
	double x_zone(double input, double range);
	double x_zone(double input);
	double x_slow(double input);
	void d_move(double x, double y, double r, double t);
	void e_move(double d, double t);
	void m_move(double d, double t);
	void s_move(DoubleSolenoid &s, bool f);
	void RobotInit() override;
	void DisabledInit() override {}
	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}
	void AutonomousInit() override;
	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override {}

private:
	/*Commands and autonomous object variables
	 * Auto modes are controlled as command objects and called to run a certain auto
	 */

	frc::Command* m_autonomousCommand = nullptr;

	MyAutoCommand a_null;                            //Null command for autonomous selection
	frc::SendableChooser<frc::Command*> a_position;  //Position of robot. Either left right or middle
	frc::SendableChooser<frc::Command*> a_objective; //Chose what to do with the box. Either switch or scale
	frc::SendableChooser<frc::Command*> a_goto;      //Choose whether to go to the left or the right during auto
	frc::SendableChooser<frc::Command*> a_test;

	//frc::SendableChooser<frc::Command*> m_chooser;

	frc::Timer t_timer;

	/*Mecanum drive train
	 * Each wheel is controlled on its own
	 * New mecanum drive class allows for easier implementation
	 * No need to invert motors as the class structure does it for you
	 */
	frc::Talon d_motor_lf { 3 }; //left front
	frc::Talon d_motor_lr { 1 }; //left rear
	frc::Talon d_motor_rf { 2 }; //right front
	frc::Talon d_motor_rr { 0 }; //right rear
	frc::MecanumDrive d_train {d_motor_lf, d_motor_lr, d_motor_rf, d_motor_rr};

	frc::Compressor hi {0};
	/*Grabber mechanism, including
	 * 1 spark for wiper motor controller
	 * 1 double solenoid for closing the arm around boxes
	 */
	frc::DoubleSolenoid g_solenoid { 1, 0 };
	frc::Spark g_motor { 5 };

	/*Elevator system, including
	 * 1 motor controller with a spliced conector for 2 SIMS
	 * Double solenoid for locking the elevators while climbing
	 */
	frc::Spark e_motor { 4 };
	frc::DoubleSolenoid e_solenoid { 2, 3 };

	frc::XboxController x_controller_l { 0 };
	frc::XboxController x_controller_r { 1 };
};

#endif
