// DIRECTIVES
#include "vex.h"

// NAMESPACE
using namespace vex;

/*
    right motor group ports - 6, 1
    left motor group ports - 4, 10
    arm group ports - 17, 18
    intake port - 8
*/

// FUNCTIONS
void initialize_motors() 
{
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

    // MAIN LOOP
    do {
        rightMotorGroup.setVelocity(Controller1.Axis3.position() - Controller1.Axis1.position(), percent);
        leftMotorGroup.setVelocity(Controller1.Axis3.position() + Controller1.Axis1.position(), percent);

        int armGroup_velocity = armGroup.velocity(percent), intake_motor_velocity = intake_motor.velocity(percent);

        if (Controller1.ButtonL1.pressing()) { // If controller L1 is being actively pulled.
            // Sets velocity to the current velocity + 10. (moves arm up)
            armGroup.spin(forward);
            armGroup.setVelocity(armGroup_velocity + 10, percent); 
        } else if (Controller1.ButtonL2.pressing()) { // Else if L1 isn't being pulled, check if L2 is.
            // Sets velocity to current velocity - 10. (moves arm down)
            armGroup.spin(forward);
            armGroup.setVelocity(armGroup_velocity - 10, percent);
        } else {  // Else if no triggers pulled.
            armGroup.setStopping(brake); 
            armGroup.stop();
        };

        if (Controller1.ButtonR1.pressing()) {
            intake_motor.spin(forward);
            intake_motor.setVelocity(intake_motor_velocity + 10);
        } else {
            intake_motor.setStopping(brake);
            intake_motor.stop();
        }
    } while (true);
}
