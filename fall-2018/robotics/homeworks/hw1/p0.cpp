#include "osl/robot_world.h"


void drive_robot(mobile_robot &robot, vec3 target) {
	while(true) {
		auto dist = robot.pos.dist(target);
		if (dist < 0.2) {
			return;
		}

		auto target_angle = angle_degrees(target);
		robot.left(target_angle);

		robot.forward(dist - 0.2);
	}
}
