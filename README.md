alvar_see
=========

Alvar SEE tracking

This code is for pattern or tag tracking. Contains two packages: 

1. Microsoft lifecam driver
2. Alvar tracking package with source code

This helps to track a robot with a paper printed tag marker attached to it in the ROS network using tf.

This code has been tested under ubuntu 12.04 64 bits and ROS hydro distribution.

Features:

- Kinect, Asus and microsoft life cam supported, (maybe others as well since the driver that we are using is generic one)
- Microsoft resolution HD of 1280 x 720 pixels
- Tf camera publisher assuming a tripod and world frame in 0,0
- Instrinsec and extrinsec paramter support via yaml configuration file inside confif folder
- alvar rviz config file available under roscd ar_track_alvar/rviz

Instructions:

- Detect your video device (camera):

		ls /dev/video0
		ls /dev/video1

- put this value inside proper launch file:

		roscd microsoft_cam_driver
		nano microsoft_life_cam.launch

- Calibrate your camera by using ros snapshot program:

		rosrun image_view image_view /image:=/microsoft_cam_driver/image_raw

- this is to take your image dataset (20 images) and later on calibrate using caltech calibration tool:

		http://www.vision.caltech.edu/bouguetj/calib_doc/htmls/example.html

NOTE: Properly adjust the value for the tripod tf inside microsoft_tf_pub.cpp file in order to receive proper data, for that
we suggest to stik a marker on the ground and verify that this marker is actually having z height equal to zero.

If it doesnt then adjust the camera angle properly or might be due to calibration error as well.

Happy calibration and tracking!

good luck

Cheers!

Oscar

comments and questions: olima_84@yahoo.com
