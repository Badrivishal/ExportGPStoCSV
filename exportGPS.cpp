// OFFBOARD POSITION CONTROL TO MANEUVER THE DRONE 

/** ROS HEADERS **/
#include<ros/ros.h>
#include<geometry_msgs/PoseStamped.h>
#include<std_msgs/Int8.h>
#include<std_msgs/Float64.h>
#include<geometry_msgs/Twist.h>
#include<mavros_msgs/State.h>
#include<mavros_msgs/SetMode.h>
#include<mavros_msgs/PositionTarget.h>
#include<mavros_msgs/CommandBool.h>
#include<mavros_msgs/CommandTOL.h>

/** PATH **/
#include<nav_msgs/Path.h>

#include<Eigen/Dense>

#include<iostream>
#include<vector>
#include<math.h>
#include<iterator>
#include<cmath>
#include <fstream>
#include <stdio.h>

// using namespace std;


geometry_msgs::PoseStamped way_pose; //this receives the waypoint every time subscriber is called

Eigen::Vector3d currPose;

int count;
bool WaypointUpdated = 0;
std::ofstream output_file;

/** waypoint callback **/

void local_pose_cb(const geometry_msgs::PoseStamped pose)
{
    output_file.open("gpsData.csv", std::ios::app);
    // output_file.setf(std::ios::fixed, std::ios::floatfield);
    // output_file.precision(0);
    output_file << pose.header.stamp.sec << pose.header.stamp.nsec << ",";
    // output_file << cur_kf->time_stamp * 1e9 << ",";
    output_file.precision(5);
    output_file  << pose.pose.position.x << ","
            << pose.pose.position.y << ","
            << pose.pose.position.z << ","
            << pose.pose.orientation.w << ","
            << pose.pose.orientation.x << ","
            << pose.pose.orientation.y << ","
            << pose.pose.orientation.z
            << std::endl;
    output_file.close();

    std::cout << "Written to file" << std::endl;
    ros::Duration(0.25).sleep();
    // currPose(0) = pose.pose.position.x;
    // currPose(1) = pose.pose.position.y;
    // currPose(2) = pose.pose.position.z;
}





int main(int argc, char** argv)
{
    ros::init(argc, argv, "drone_control");
    ros::NodeHandle n;

    ros::Subscriber loc = n.subscribe<geometry_msgs::PoseStamped>("/mavros/local_position/pose",10,local_pose_cb);

    ros::spin();
    return 0;
}