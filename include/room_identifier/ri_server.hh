#include <iostream>
#include <string.h>
#include <fstream>
#include <sys/stat.h>
#include <ctime>
#include <unistd.h>

#include "ros/ros.h"
#include "room_identifier/PlaceName.h"

class RIServer
{
	ros::NodeHandle nh_;
	ros::ServiceServer service_;
	std::string in_file_, out_file_;

    public:
    	RIServer(ros::NodeHandle n);
	bool handleRequest(room_identifier::PlaceName::Request &req,
		room_identifier::PlaceName::Response &res);
	bool checkIdentifyStatus(std::string &r);
};

