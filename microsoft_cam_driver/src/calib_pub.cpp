/* 
 * Author : Oscar Lima, olima_84@yahoo.com
 * check : http://docs.ros.org/api/sensor_msgs/html/msg/CameraInfo.html
 * 
 * */

#include "ros/ros.h"
#include "sensor_msgs/CameraInfo.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "microsoft_calib_pub");
	ros::NodeHandle nh;
	ros::Publisher microsoft_calib_pub = nh.advertise<sensor_msgs::CameraInfo>("microsoft/camera_info", 1);
	ros::Rate loop_rate(10);

	sensor_msgs::CameraInfo microsoft_info;
	
	//filling message with instrinsic calib parameters
	microsoft_info.header.frame_id = "/microsoft_camera_frame";
	microsoft_info.height = 480; //720 , 480?
	microsoft_info.width = 640; //1280 , 640?
	microsoft_info.distortion_model = "plumb_bob";
	
	//distortion_params = {0.0, 0.0, 0.0, 0.0, 0.0};
	std::vector<double> distortion_params;
	distortion_params.push_back(0.061711155665299);
	distortion_params.push_back(-0.146842820043531);
	distortion_params.push_back(-0.010612937121862);
	distortion_params.push_back(-0.001949348765289);
	distortion_params.push_back(0.0);
	microsoft_info.D = distortion_params;
	
	//intrinsec camera matrix
	microsoft_info.K = (boost::array<double, 9ul>)
	{595.002389161487486, 0.0, 325.490867387017431,
	0.0, 597.429908922273171, 222.165979363201757,
	0.0, 0.0, 1.0};
	
	//Rectificacion matrix (stereo cameras only), then identity matrix
	microsoft_info.R = (boost::array<double, 9ul>)
	{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

	//Projection matrix
	microsoft_info.P = (boost::array<double, 12ul>)
	{0.0006, -0.0076, -0.0091, 6.6082, -0.0101, 0.0, -0.0034, 4.0526, 0.0, 0.0, 0.0, 0.0071};
	
	microsoft_info.binning_x = 0;
	microsoft_info.binning_y = 0;
	
	microsoft_info.roi.x_offset = 0;
	microsoft_info.roi.y_offset = 0; 
	microsoft_info.roi.height = 0;
	microsoft_info.roi.width = 0;
	microsoft_info.roi.do_rectify = false;
	
	while (ros::ok())
	{

		microsoft_calib_pub.publish(microsoft_info);

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}
/*
header: 
  seq: 52
  stamp: 
    secs: 0
    nsecs: 0
  frame_id: /microsoft_camera_frame
height: 720
width: 1280
distortion_model: plumb_bob
D: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
K: [994.7111492346629, 0.0, 645.0503735554145, 0.0, 992.6853245110515, 376.5553039396862, 0.0, 0.0, 1.0]
R: [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
P: [0.0006, -0.0076, -0.0091, 6.6082, -0.0101, 0.0, -0.0034, 4.0526, 0.0, 0.0, 0.0, 0.0071]
binning_x: 0
binning_y: 0
roi: 
  x_offset: 0
  y_offset: 0
  height: 0
  width: 0
  do_rectify: False
*/