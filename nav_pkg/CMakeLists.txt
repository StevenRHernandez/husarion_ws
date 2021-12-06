cmake_minimum_required(VERSION 3.0.2)
project(tutorial_pkg)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
  nav_msgs
  sensor_msgs
)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(drive_controller_node src/drive_controller.cpp)
add_executable(telemetry_handler_node src/telemetry_handler.cpp)

target_link_libraries(drive_controller_node
  ${catkin_LIBRARIES}
)

target_link_libraries(telemetry_handler_node
  ${catkin_LIBRARIES}
)
