#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "robot_tf_pub");
	ros::NodeHandle node;
	ros::Rate rate(20.0); //for running the node in a loop at 10 hz
	
	static tf::TransformBroadcaster tf_broadcaster;
	tf::StampedTransform fake_tf;
	
	ros::Time now = ros::Time::now();
	ros::Time latest_available_transform = ros::Time(0);
	ros::Duration tf_patience = ros::Duration(0.2);
	
	while (node.ok())
	{
		//creating fake transform from base_link but shifted to an arbitrary position
		try
		{
			fake_tf.setOrigin( tf::Vector3(0.0, 0.0, -0.15) ); //robot tag is 15 cm height
			fake_tf.setRotation( tf::createQuaternionFromRPY(-0.4, 0.0, 0.0) );
			tf_broadcaster.sendTransform(tf::StampedTransform(fake_tf, ros::Time::now(), "ar_marker_7", "lego_robot"));
		}
		catch (tf::TransformException ex)
		{
			ROS_ERROR("%s",ex.what());
		}
			
		rate.sleep();
	}
	return 0;
};
