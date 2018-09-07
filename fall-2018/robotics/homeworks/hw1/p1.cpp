#include "osl/robot_world.h"


double shoot_lidar(const mobile_robot &robot, double angle_degrees=0);


void move_until_obstacle(mobile_robot &robot, double turn, double dist) {
	robot.left(turn);
	auto nearest_obj = shoot_lidar(robot);

	if (nearest_obj < dist) {
		robot.forward(nearest_obj - 0.2);
	} else {
		robot.forward(dist - 0.2);
	}
}


void move_around_obstacles(mobile_robot & robot) {
	auto nearest_obj = shoot_lidar(robot);

	robot.left(90);

	while(true) {
		auto obj = shoot_lidar(robot);

		if (obj > nearest_obj * 2) {
			robot.forward(min(obj-.1, 1.));
			return;
		} else {
			nearest_obj = obj;
			robot.left(1);
		}
	}
}


void drive_robot(mobile_robot &robot,vec3 target) {
	auto i = 0;

	while(++i < 100) {
		auto turn = angle_degrees(target - robot.pos) - robot.angle;
		auto dist = robot.pos.dist(target);

		move_until_obstacle(robot, turn, dist);

		if (robot.pos.dist(target) < .2) {
			return;
		}

		move_around_obstacles(robot);
	}
}
