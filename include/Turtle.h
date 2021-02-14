#pragma once
/**
 * @file Beep.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <behaviortree_cpp_v3/action_node.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>
#include <math.h>
#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <optional>



class Turtle : public BT::SyncActionNode
{
 public:
    Turtle(const std::string& name, const BT::NodeConfiguration& config);
    static BT::PortsList providedPorts();
    BT::NodeStatus       tick() override;
 private:
    ros::NodeHandle n;
    double current_distance;
    ros::Publisher velocity_publisher;
    geometry_msgs::Twist vel_msg;
};