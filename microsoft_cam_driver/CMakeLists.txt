cmake_minimum_required(VERSION 2.8.3)
project(microsoft_cam_driver)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
  tf
)

catkin_package(
#INCLUDE_DIRS include
#  LIBRARIES tracker_listener
#  CATKIN_DEPENDS roscpp std_msgs tf
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

#declaring camera tf publisher executable
add_executable(camera_tf src/microsoft_tf_pub.cpp)

#linking previous declared executable with ros libraries
target_link_libraries(camera_tf
   ${catkin_LIBRARIES}
)
