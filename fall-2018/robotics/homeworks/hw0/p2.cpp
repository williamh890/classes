#include "osl/robot_world.h"


void drive_robot(mobile_robot &robot)
{
	// call robot.forward(distance)  and robot.left(angle)  here!
	robot.forward(2.5);
	robot.left(85);
	robot.forward(3.0);
	robot.left(265.0);
	robot.forward(.3);
}
