#include "Robot.h"

void Robot::RobotPeriodic() 
{

  //Toggle between the two cameras
  if(cameraToggle && controller.GetRawButton(1)) {
    camServer.SetSource(camFront);
  }
  if(!cameraToggle && controller.GetRawButton(1)) {
    camServer.SetSource(camRear);
  }
}

void Robot::TeleopPeriodic()
{
  // Drive with arcade style controls
  diffDrive.ArcadeDrive(controller.GetY(), controller.GetX());

  //"Intake mode" that allows the user to set the intake running constantly until a ball is caught
  if (controller.GetRawButton(9) && !(controller.GetRawAxis(2) > 0))
  {
    intakeMode = true;
    cargoMotor.Set(.25);
  }
  if (controller.GetRawAxis(2) > 0)
  {
    cargoMotor.Set(controller.GetRawAxis(2));
  }
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
