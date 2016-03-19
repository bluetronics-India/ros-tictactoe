#include "Player.h"
#include "ros/ros.h"

int main(int argc, char **argv)
{
	
  ros::init(argc, argv, "player1");
  

  ROS_INFO("Started Player %i.\n",atoi(argv[1]));

  player player(atoi(argv[1]));
  player.Loop();

  return 0;

}