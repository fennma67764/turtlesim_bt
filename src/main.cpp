/**
 * @file turtlesim_bt.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../include/Turtle.h"
#include <behaviortree_cpp_v3/bt_factory.h>
#include <behaviortree_cpp_v3/loggers/bt_cout_logger.h>
#include <behaviortree_cpp_v3/loggers/bt_zmq_publisher.h>
#include <ros/package.h>  

#include "ros/ros.h"
#include <ros/package.h>
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
#include <iostream>



int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtlesim_bt");

    BT::BehaviorTreeFactory factory;

    factory.registerNodeType<Turtle>("Turtle");

    BT::Tree tree = factory.createTreeFromFile(
        ros::package::getPath("turtlesim_bt") + "/trees/turtlesim_bt.xml");

    BT::StdCoutLogger cout_logger(tree);

    //Creates Link between ROS and Groot
    BT::PublisherZMQ zmq_publisher(tree);
    
    //Objekt (turtle) der Klasse (Turtle) muss nicht gebildet werden, da
    //es über den BT läuft


    int timer = 0;
    while(ros::ok())
    {
        std::cout << "\n--- executeTick() " << std::to_string(timer) << "---"
                << std::endl;
        tree.tickRoot();    
        sleep(1);
        timer++;
    }
    return 0;
    

}