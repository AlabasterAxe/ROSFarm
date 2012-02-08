#include "ros/ros.h"
#include "dynamixel_msgs/JointState.h"
#include "std_msgs/Float64.h"

//for system()
#include <cstdlib>
#include <string>

/*
//for forking
#include <sys/types.h>
#include <unistd.h>
*/

//for testing
#include <iostream>

#include <sstream>
std::string ftos (float number){
	std::ostringstream buff;
	buff<<number;
	return buff.str();
}

//#include "PublishFloat64.cpp"

class Gripper {
private:
	dynamixel_msgs::JointState right_grip;
	ros::Subscriber right_sub;
	ros::Publisher right_pub;
	
	dynamixel_msgs::JointState left_grip;
	ros::Subscriber left_sub;
	ros::Publisher left_pub;
	
	void right_state_Callback(const dynamixel_msgs::JointState::ConstPtr& msg) {
		right_grip = *msg;
/*
		right_grip.header.seq = msg->header.seq;
		right_grip.header.stamp = msg->header.stamp;
		right_grip.header.frame_id = msg->header.frame_id;
		right_grip.name = msg->name;
		right_grip.motor_ids = msg->motor_ids;
		right_grip.motor_temps = msg->motor_temps;
		right_grip.goal_pos = msg->goal_pos;
		right_grip.current_pos = msg->current_pos;
		right_grip.error = msg->error;
		right_grip.velocity = msg->velocity;
		right_grip.load = msg->load;
		right_grip.is_moving = msg->is_moving;
*/
	}
	
	void left_state_Callback(const dynamixel_msgs::JointState::ConstPtr& msg) {
		left_grip = *msg;
/*
		left_grip.header.seq = msg->header.seq;
		left_grip.header.stamp = msg->header.stamp;
		left_grip.header.frame_id = msg->header.frame_id;
		left_grip.name = msg->name;
		left_grip.motor_ids = msg->motor_ids;
		left_grip.motor_temps = msg->motor_temps;
		left_grip.goal_pos = msg->goal_pos;
		left_grip.current_pos = msg->current_pos;
		left_grip.error = msg->error;
		left_grip.velocity = msg->velocity;
		left_grip.load = msg->load;
		left_grip.is_moving = msg->is_moving;
*/
	}

public:
	Gripper() {
		ros::NodeHandle nh;
		nh = ros::NodeHandle::NodeHandle();
/*
//		pid_t pID = fork();
		
		//launch the servo manager as another process
//		if (pID == 0) {
		system("roslaunch barrem4_handeye gripper_manager.launch");
//		}
		
		//continue on your merry way
		system("roslaunch barrem4_handeye gripper_spawner.launch");
*/		
		right_sub = nh.subscribe("right_gripper_controller/state", 1, &Gripper::right_state_Callback, this);
		left_sub = nh.subscribe("left_gripper_controller/state", 1, &Gripper::left_state_Callback, this);
		
		right_pub = nh.advertise<std_msgs::Float64>("right_gripper_controller/command", 1, true);
		left_pub = nh.advertise<std_msgs::Float64>("left_gripper_controller/command", 1), true;
	}
	
	Gripper(const std::string &ns, const ros::M_string &remappings) {
		ros::NodeHandle nh;
		nh = ros::NodeHandle::NodeHandle(ns, remappings);
/*
//		pid_t pID = fork();
		
		//launch the servo manager as another process
//		if (pID == 0) {
		system("roslaunch barrem4_handeye gripper_manager.launch");
//		}
		
		//continue on your merry way
		system("roslaunch barrem4_handeye gripper_spawner.launch");
*/		
		right_sub = nh.subscribe("right_gripper_controller/state", 1, &Gripper::right_state_Callback, this);
		left_sub = nh.subscribe("left_gripper_controller/state", 1, &Gripper::left_state_Callback, this);
		
		right_pub = nh.advertise<std_msgs::Float64>("right_gripper_controller/command", 1);
		left_pub = nh.advertise<std_msgs::Float64>("left_gripper_controller/command", 1);
	}
	
	void move_r(float target_angle) {
ros::spinOnce();
		std_msgs::Float64 temp;
		temp.data = target_angle;
		right_pub.publish(temp);
ros::Duration(1).sleep();
/*
std::string command = "rostopic pub -1 right_gripper_controller/command std_msgs/Float64 -- ";
command += ftos(target_angle/2);
system( command.c_str() );
ros::spinOnce();
std::cout << "After sketchy publish: " << right_grip.current_pos << std::endl;
*/
	}
	
	void move_l(float target_angle) {
		std_msgs::Float64 temp;
		temp.data = target_angle;
		left_pub.publish(temp);
	}
	
	float get_pos_r() {ros::spinOnce(); return right_grip.current_pos;}
	float get_pos_l() {ros::spinOnce(); return left_grip.current_pos;}
	
	bool r_is_moving() {ros::spinOnce(); return right_grip.is_moving;}
};
