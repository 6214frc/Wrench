/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include <frc/Spark.h>
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>

/**
 * This is (a version) of FRC Team 6214's robot code for 2019
 * Very simple, but hopefully self-explanitory code that any team
 * can look at and borrow from
 */
class Robot : public frc::TimedRobot
{
    void TeleopPeriodic() override{
	    diffDrive.ArcadeDrive(controller.GetRawAxis(5), controller.GetRawAxis(4));
    };

   private:
    //A single Xbox controller
    frc::Joystick controller{0};

    //Drive train objects
    frc::Spark leftMotor{0};
    frc::Spark rightMotor{1};
    frc::DifferentialDrive diffDrive{leftMotor, rightMotor};
};
