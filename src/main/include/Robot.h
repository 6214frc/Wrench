/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include <frc/Spark.h>
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <cameraserver/CameraServer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTable.h>


/**
 * This is (a version) of FRC Team 6214's robot code for 2019
 * Very simple, but hopefully self-explanitory code that any team
 * can look at and borrow from
 */
class Robot : public frc::TimedRobot
{
    void RobotPeriodic() override;
    void RobotInit() override;
    void TeleopPeriodic() override;
    void AutonomousPeriodic() override;
    void PlayerControl();

    private:
    //A single Xbox controller
    frc::Joystick controller{0};

    //Drive train objects
    frc::Spark leftMotor{0};
    frc::Spark rightMotor{1};
    frc::DifferentialDrive diffDrive{leftMotor, rightMotor};

    //Intake for "cargo"
    frc::Spark cargoMotor{3};

    //ShuffleBoard & NetworkTable entry stuffs
    nt::NetworkTableEntry NTDriveTrain;

    //Cameras used for viewing at the Driver station
    //Sink is used to switch between cameras and (hopefully) save on bandwidth and latency
    //TODO: Maybe use vision processing to aid driver
    cs::UsbCamera camFront = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
    cs::UsbCamera camRear = frc::CameraServer::GetInstance()->StartAutomaticCapture(1);
    cs::VideoSink camServer = frc::CameraServer::GetInstance()->GetServer();

    //Msc variables
    bool intakeMode = false;
    bool cameraToggle = false;
    int speedScalingFactor = 4; // Higher the Scaling factor the slower it accelerates
    double speed = 0;
    double previousSpeed = 0;

};