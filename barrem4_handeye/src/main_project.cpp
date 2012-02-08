#include "Gripper.h"
#include <iostream>

int main(int argc, char** argv) {
	ros::init(argc, argv, "main_project");
	Gripper grip;
	
	float testing = 0.1;
	while (testing < 1.4) {
		std::cout << "Goal: " << testing << std::endl;
		grip.move_r(testing);
		std::cout << "Final: " << grip.get_pos_r() << std::endl << std::endl;
		
		testing += 0.1;
	}

	return 0;
}
