#include "Robot.h"
#include <iostream>

void Robot::RobotPeriodic() 
{

  //Toggle between the two cameras
  if(cameraToggle && controller.GetRawButton(1)) {
    camServer.SetSource(camFront);
    cameraToggle = !cameraToggle;
  }
  if(!cameraToggle && controller.GetRawButton(1)) {
    camServer.SetSource(camRear);
    cameraToggle = !cameraToggle;
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
  if(controller.GetRawAxis(5) > speed) {
  speed = speed + controller.GetRawAxis(5)/16;
  } else if(controller.GetRawAxis(5) < speed) {
    speed = speed - controller.GetRawAxis(5)/16;
  }
  diffDrive.ArcadeDrive(-speed, controller.GetRawAxis(4) * .8);

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
