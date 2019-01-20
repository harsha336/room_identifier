#include "ros/ros.h"
#include "room_identifier/ri_server.hh"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "add_two_ints_server");
  ros::NodeHandle n;

  RIServer rs(n);
  ros::spin();
  return 0;
}
