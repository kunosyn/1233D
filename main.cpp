// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// rightMotorGroup      motor_group   6, 1            
// leftMotorGroup       motor_group   4, 10           
// armGroup             motor_group   11, 20          
// intakeMotor          motor         8               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

// DIRECTIVES
#include "vex.h"

// NAMESPACE
using namespace vex;

/*
  right motor group ports - 6, 1
  left motor group ports - 4, 10
  arm group ports - 11, 20
  intake motor port - 8
*/



// FUNCTIONS
void move_arms_up()
{
  if (armGroup.position(degrees) < 120) // Checks to make sure motors have not exceeded max degrees.
  {
    armGroup.spin(forward);
    armGroup.setVelocity(40, percent);
  }
}

void move_arms_down()
{
  armGroup.spin(reverse);
  armGroup.setVelocity(40, percent);
}


void stop_arms() {
  armGroup.stop();
}

void move_intake_up()
{
  intakeMotor.spin(forward);
  intakeMotor.setVelocity(45, percent);
}

void move_intake_down()
{
  intakeMotor.spin(reverse);
  intakeMotor.setVelocity(45, percent);
}

void stop_intake()
{
  intakeMotor.stop();
}

void initialize_motors() 
{
  armGroup.setPosition(0, degrees);

  rightMotorGroup.spin(forward);
  leftMotorGroup.spin(forward);
    
  rightMotorGroup.setVelocity(0, percent);
  leftMotorGroup.setVelocity(0, percent);
  armGroup.setVelocity(0, percent);
}

int main() 
{
  // Starts drive motors and resets every motor's velocity.
  initialize_motors();

  // MOTOR CONTROLS
  armGroup.setStopping(hold);
  intakeMotor.setStopping(brake);

  // MAIN LOOP
  do {
    rightMotorGroup.setVelocity(Controller1.Axis3.position() - Controller1.Axis1.position(), percent); // Drivetrain right group.
    leftMotorGroup.setVelocity(Controller1.Axis3.position() + Controller1.Axis1.position(), percent); // Drivetrain left group.

    Controller1.ButtonL1.pressed(move_arms_up); // If L1 is pulled, move arm group up.
    Controller1.ButtonL1.released(stop_arms); // When L1 is released, stop the arms from moving.
    Controller1.ButtonL2.pressed(move_arms_down); // If L2 is pulled, move arm group down.
    Controller1.ButtonL2.released(stop_arms); // When L2 released, stop arms from moving.

    Controller1.ButtonR1.pressed(move_intake_up); // If R1 is pulled, move intake up.
    Controller1.ButtonR1.released(stop_intake); // When R1 is released, stop intake from moving.
    Controller1.ButtonR2.pressed(move_intake_down); // If R2 is pressed, move intake down.
    Controller1.ButtonR2.released(stop_intake); // If R1 is released stop intake from moving.
  } while (true);
}
