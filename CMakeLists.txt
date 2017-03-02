cmake_minimum_required(VERSION 2.8.3)
project(omnijoy)

find_package(catkin REQUIRED COMPONENTS geometry_msgs sensor_msgs roscpp)
catkin_package()

add_executable(turtle_teleop_joy src/turtle_teleop_joy.cpp)
target_link_libraries(turtle_teleop_joy ${catkin_LIBRARIES})
