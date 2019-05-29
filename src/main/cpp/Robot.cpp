#include "Robot.h"
#include <iostream>

void Robot::AutonomousPeriodic() {
  PlayerControl();
}

void Robot::TeleopPeriodic() {
  PlayerControl();
}

void Robot::RobotInit() {     
}

void Robot::RobotPeriodic() {
  NTDriveTrain.SetDouble(controller.GetRawAxis(5));
  NTIntake.SetDouble(cargoMotor.Get());

  //Toggle between the two cameras
  if(controller.GetRawButtonPressed(1)) {
    cameraToggle = !cameraToggle;
    camServer.SetSource(cameraToggle ? camFront : camRear);
  }
}

void Robot::PlayerControl() {
  /**
   * Acceleration of the drive train is decreased by adding the difference 
   * between the current speed and the target speed divided by a scaling factor.
   **/

  // Drive with arcade style controls
  speed += (controller.GetRawAxis(5) - previousSpeed)/speedScalingFactor;
  diffDrive.ArcadeDrive(speed * .8, controller.GetRawAxis(4) * .7);
  previousSpeed = speed;

  //"Intake mode" that allows the user to set the intake running constantly until a ball is caught
  if (controller.GetRawButton(9) && (controller.GetRawAxis(2) < .02)) {
    cargoMotor.Set(.5);
    intakeMode = true;
  }

  if (controller.GetRawAxis(2) > .02) {
    intakeMode = false;
    cargoMotor.Set(controller.GetRawAxis(2));

  } else if (!intakeMode) {
    cargoMotor.Set(0);
    
  }

  if (controller.GetPOV() == 0){
    hatchMotor.Set(1.0);
  } else if (controller.GetPOV(180) == 180) {
    hatchMotor.Set(-1.0);
  }

}

int main(){return frc::StartRobot<Robot>();}