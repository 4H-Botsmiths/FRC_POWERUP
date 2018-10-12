/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ExampleCommand.h"

ExampleCommand::ExampleCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(&Robot::chassis);
}

// Called just before this Command runs the first time
void ExampleCommand::Initialize(frc::MecanumDrive &tran) {
	std::cout << "started driving" << std::endl;
	tran.DriveCartesian(1.0, 0.0, 0.0);
	std::cout << "start wait1" << std::endl;
	frc::Wait(2.0);
	std::cout << "end wait1" << std::endl;
	tran.DriveCartesian(-1.0, 0.0, 0.0);
}

// Called repeatedly when this Command is scheduled to run
void ExampleCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ExampleCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ExampleCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExampleCommand::Interrupted() {}
