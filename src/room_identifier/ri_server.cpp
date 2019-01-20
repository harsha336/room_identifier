#include "room_identifier/ri_server.hh"

RIServer::RIServer(ros::NodeHandle n) :
	nh_(n)
{
	service_ = nh_.advertiseService("room_name", &RIServer::handleRequest, this);
	in_file_ = "/tmp/matlab_net_req";
	out_file_ = "/tmp/matlab_net_ret";
	ROS_INFO("RIServer::RIServer: Server started!");
}
bool RIServer::handleRequest(room_identifier::PlaceName::Request  &req,
         room_identifier::PlaceName::Response &res)
{
	struct stat buf;
	if(stat(in_file_.c_str(), &buf) != 0)
	{
		ROS_INFO("Create new request to matlab!");
		std::ofstream f(in_file_.c_str());
		std::string ret;
		if(checkIdentifyStatus(ret))
		{
			res.ret_code = 0;
			res.name = ret;
		}
		else
			res.ret_code = -1;
		return true;
	}
	else
	{
		ROS_ERROR("Improper file handling!");
		res.ret_code = -1;
		return true;
	}
}

bool RIServer::checkIdentifyStatus(std::string &r)
{
	ROS_INFO("RIServer::checkIdentifyStatus: Method entered!");
	struct stat buf;
	clock_t start = clock();
	std::string slash = "\\|/-";
	int count = 0;
	while(stat(out_file_.c_str(), &buf) != 0)
	{
		clock_t cur = clock();
		double elapsed = double(cur - start) / CLOCKS_PER_SEC;
		std::string print_log = "Processing..." + slash[count%4];
		if(elapsed > 6000)
		{
			ROS_INFO("Timeout!");
			return false;
		}
		//std::cout << print_log << "\r";
		count++;
	}
	//ROS_INFO_STREAM("\nProcessed!\n");
	std::ifstream f(out_file_.c_str());
	if(f.is_open())
	{
		getline(f, r);
		f.close();
		remove(out_file_.c_str());
		remove(in_file_.c_str());
		return true;
	}
	//ROS_ERROR("Unable to open response file!");
	return false;
}

