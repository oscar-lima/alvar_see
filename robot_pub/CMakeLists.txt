cmake_minimum_required(VERSION 2.8.3)
project(robot_tf_pub)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
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

add_executable(robot_tf_pub src/robot_tf_pub.cpp)

target_link_libraries(robot_tf_pub
   ${catkin_LIBRARIES}
)