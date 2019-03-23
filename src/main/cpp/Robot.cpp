#include "Robot.h"
#include <iostream>

void Robot::RobotPeriodic() 
{

  //Toggle between the two cameras
  if(controller.GetRawButtonPressed(1)) {
    cameraToggle = !cameraToggle;
    camServer.SetSource(cameraToggle ? camFront : camRear);
  }
}

void Robot::AutonomousPeriodic() {
  PlayerControl();
}
void Robot::TeleopPeriodic()
{
  PlayerControl();
}

void Robot::PlayerControl() {
  
  // Drive with arcade style controls
  speed += (controller.GetRawAxis(5) - previousSpeed)/64;
  diffDrive.ArcadeDrive(-speed, controller.GetRawAxis(4) * .8);
  previousSpeed = speed;

  //"Intake mode" that allows the user to set the intake running constantly until a ball is caught
  if (controller.GetRawButton(9) && (controller.GetRawAxis(2) == 0))
  {
    cargoMotor.Set(.2);
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
