#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <fstream>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <vector>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "see_data_logger");
	ros::NodeHandle nh("~");

	tf::TransformListener listener;
	tf::StampedTransform transform;

	// open file 
	std::ofstream log_file;
	log_file.open ("/home/oscar/see.log");
	
	//structure of the log file
	log_file << "timestamp; x; y; z; yaw;"  << std::endl;
	ros::Rate loop_rate(1);

	while (ros::ok())
	{
		ros::spinOnce();
		
		//looking for lego robot
		try
		{
			//if lego is found then get the lastest available transform
			listener.lookupTransform("/world", "/lego_robot", ros::Time(0), transform);
			//write the origin of the frame to the log file
			log_file << transform.stamp_ << ";" << transform.getOrigin().x() << "; " << transform.getOrigin().y() << "; " << transform.getOrigin().z() << "; ";
			
			//parsing quaternion into roll pitch yaw
			tf::Quaternion q(transform.getRotation());
			double yaw, pitch, roll;
			tf::Matrix3x3(q).getEulerYPR(yaw,pitch,roll);

			//writing yaw in log file
			log_file << yaw << ";";

			//change of line
			log_file << std::endl;
		} 
		catch (tf::TransformException ex)
		{
			//ROS_ERROR("Could not lookup transform between /world and /lego_robot: %s",ex.what());
		}

		//sleep for 1/10 hz
		loop_rate.sleep();
	}

	log_file.close();

	return 0;
}
