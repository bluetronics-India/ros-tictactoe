#include "Server.h"
#include "ros/ros.h"

int main(int argc, char **argv)
{
	
  ros::init(argc, argv, "server");

  ROS_INFO("Started Server.");

  server server;
  server.Loop();

  return 0;

}