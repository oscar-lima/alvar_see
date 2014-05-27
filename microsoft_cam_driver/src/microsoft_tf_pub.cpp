#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "microsoft_tf_pub");
	ros::NodeHandle node;
	ros::Rate rate(2.0); //for running the node in a loop at 2 hz
	
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
			fake_tf.setOrigin( tf::Vector3(0.0, 0.0, 0.5) ); //shifting the origin
			fake_tf.setRotation( tf::createQuaternionFromRPY(2.356194, 0.0, 0.0) ); //preserving the orientation of the parent
			tf_broadcaster.sendTransform(tf::StampedTransform(fake_tf, ros::Time::now(), "/world", "/microsoft_camera_frame"));
		}
		catch (tf::TransformException ex)
		{
			ROS_ERROR("%s",ex.what());
		}
			
		rate.sleep();
	}
	return 0;
};
