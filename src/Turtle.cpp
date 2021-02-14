/**
 * @file Turtle.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "../include/Turtle.h"



Turtle::Turtle(const std::string& name, const BT::NodeConfiguration& config)
   : BT::SyncActionNode(name, config)
{ }

BT::PortsList Turtle::providedPorts()
{
   //Port anmelden
   return {BT::InputPort<int>("enable"), 
   BT::InputPort<double>("distance"),
   BT::InputPort<double>("vel_x"),
   BT::InputPort<double>("vel_y"),
   BT::InputPort<int>("direction")};
}

//Implementation goes here
BT::NodeStatus Turtle::tick()
{

   //static to make it posible to change variable in programm.
   BT::Optional<int> enable = getInput<int>("enable");
   BT::Optional<int> direction = getInput<int>("direction");
   BT::Optional<double> vel_x = getInput<double>("vel_x");
   BT::Optional<double> vel_y = getInput<double>("vel_y");
   BT::Optional<double> distance = getInput<double>("distance");
   //int enable = getInput<int>("enable");

   velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

   ros::Rate loop_rate(10);



    if(enable==1)
    {
            //set linear velocity in direction

        if (direction==1){
            vel_msg.linear.x = abs(*vel_x); //forward
            vel_msg.linear.y = abs(*vel_y); //left
        }
            
        else{
            vel_msg.linear.x = -abs(*vel_x); //backward
            vel_msg.linear.y = -abs(*vel_y); //right
        }

        //Z-Velocity always 0
        vel_msg.linear.z=0;

        //set angular velocity to always 0
        vel_msg.angular.x =0 ;
        vel_msg.angular.y = 0;
        vel_msg.angular.z = 0;

        //t0: current time
        double t0=ros::Time::now().toSec();
        current_distance = 0;
        ros::Rate loop_rate(10);
        do{
            velocity_publisher.publish(vel_msg);
            double t1 = ros::Time::now().toSec();
            current_distance = pow(vel_msg.linear.x * (t1-t0), 2) + pow(vel_msg.linear.y * (t1-t0), 2);
            ros::spinOnce();
            ROS_INFO("current_distance %f", current_distance);
            loop_rate.sleep();
         }while (current_distance < distance);

        vel_msg.linear.x = 0;
        vel_msg.linear.y = 0;
        velocity_publisher.publish(vel_msg);
    }
   

   /**
    * @brief If for Enable
    * 
    */
    /*
   if (enable == 1)
   {
      vel_msg.linear.x = 1.0;
      vel_msg.linear.y = 0.0;
      ros::spinOnce();
      velocity_publisher.publish(vel_msg);
      //ros::spinOnce();
      std::cout << "Beep" << std::endl;
      //printf("Enable = %i", enable);
      std::cout << "Enable= " << enable.value() << std::endl;
      sleep(2);
      //enable = 2;
   }
   else if (enable == 2)
   {
       vel_msg.linear.x = 0.0;
       vel_msg.linear.y = 1.0;
      velocity_publisher.publish(vel_msg);
      ros::spinOnce();
      std::cout << "Boop" << std::endl;
      std::cout << "Enable= " << enable.value() << std::endl;
      sleep(2);
      //enable = 3;
   }
   else if (enable == 3)
   {
       vel_msg.linear.x = -1.0;
       vel_msg.linear.y = 0.0;
      velocity_publisher.publish(vel_msg);
      ros::spinOnce();
      std::cout << "Boop" << std::endl;
      std::cout << "Enable= " << enable.value() << std::endl;
      sleep(2);
      //enable = 3;
   }
   else
   {
       vel_msg.linear.x = 0.0;
       vel_msg.linear.y = -1.0;
      velocity_publisher.publish(vel_msg);
      std::cout << "Not Beep" << std::endl;
      ros::spinOnce();
      std::cout << "Enable= " << enable.value() << std::endl;
      sleep(2);
      //enable = 1;
   }
   */
   ros::spinOnce();
   loop_rate.sleep();

   return BT::NodeStatus::SUCCESS;
}