cmake_minimum_required(VERSION 3.5)
project(dobot)

# # Default to C99
# if(NOT CMAKE_C_STANDARD)
#   set(CMAKE_C_STANDARD 99)
# endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


## Add support for C++11, supported in ROS Kinetic and newer
# add_definitions(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(roscpp REQUIRED)
find_package(rospy REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(message_generation REQUIRED)
find_package(genmsg REQUIRED)
find_package(geometry_msgs REQUIRED)
# find_package(message_package REQUIRED)
# ament_register_extension(
#   "rosidl_generate_interfaces"
# )

rosidl_generate_interfaces(${PROJECT_NAME}
  # ${msg_files}
  ${srv_files}
  # DEPENDENCIES std_msgs
  "srv/SetCmdTimeout.srv"
  "srv/GetDeviceSN.srv"
  "srv/SetDeviceName.srv"
  "srv/GetDeviceName.srv"
  "srv/GetDeviceVersion.srv"
  "srv/GetPose.srv"
  "srv/GetAlarmsState.srv"
  "srv/ClearAllAlarmsState.srv"
  "srv/SetHOMEParams.srv"
  "srv/GetHOMEParams.srv"
  "srv/SetHOMECmd.srv"
  "srv/SetEndEffectorParams.srv"
  "srv/GetEndEffectorParams.srv"
  "srv/SetEndEffectorLaser.srv"
  "srv/GetEndEffectorLaser.srv"
  "srv/SetEndEffectorSuctionCup.srv"
  "srv/GetEndEffectorSuctionCup.srv"
  "srv/SetEndEffectorGripper.srv"
  "srv/GetEndEffectorGripper.srv"
  "srv/SetJOGJointParams.srv"
  "srv/GetJOGJointParams.srv"
  "srv/SetJOGCoordinateParams.srv"
  "srv/GetJOGCoordinateParams.srv"
  "srv/SetJOGCommonParams.srv"
)

## Generate messages in the 'msg' folder
# set(msg_files
#   message_package_DIR
# )

## Generate services in the 'srv' folder
set(srv_files

  # 
  # 
  # 
  # "srv/GetJOGCommonParams.srv"
  # "srv/SetJOGCmd.srv"
  # "srv/SetPTPJointParams.srv"
  # "srv/GetPTPJointParams.srv"
  # "srv/SetPTPCoordinateParams.srv"
  # "srv/GetPTPCoordinateParams.srv"
  # "srv/SetPTPJumpParams.srv"
  # "srv/GetPTPJumpParams.srv"
  # "srv/SetPTPCommonParams.srv"
  # "srv/GetPTPCommonParams.srv"
  # "srv/SetPTPCmd.srv"
  # "srv/SetCPParams.srv"
  # "srv/GetCPParams.srv"
  # "srv/SetCPCmd.srv"
  # "srv/SetARCParams.srv"
  # "srv/GetARCParams.srv"
  # "srv/SetARCCmd.srv"
  # "srv/SetWAITCmd.srv"
  # "srv/SetTRIGCmd.srv"
  # "srv/SetIOMultiplexing.srv"
  # "srv/GetIOMultiplexing.srv"
  # "srv/SetIODO.srv"
  # "srv/GetIODO.srv"
  # "srv/SetIOPWM.srv"
  # "srv/GetIOPWM.srv"
  # "srv/GetIODI.srv"
  # "srv/GetIOADC.srv"
  # "srv/SetEMotor.srv"
  # "srv/GetInfraredSensor.srv"
  # "srv/SetInfraredSensor.srv"
  # "srv/SetColorSensor.srv"
  # "srv/GetColorSensor.srv"
  # "srv/SetQueuedCmdStartExec.srv"
  # "srv/SetQueuedCmdStopExec.srv"
  # "srv/SetQueuedCmdForceStopExec.srv"
  # "srv/SetQueuedCmdClear.srv"

)

ament_export_dependencies(rosidl_default_runtime)

ament_export_dependencies(roscpp rospy std_msgs message_runtime geometry_msgs)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
  PATTERN "*~"
  EXCLUDE)


ament_export_include_directories(src/DobotDll_x86)

install(
  DIRECTORY src/
  DESTINATION DobotDll_x86
)

ament_export_include_directories(src/DobotDll_x64)

install(
  DIRECTORY src/
  DESTINATION DobotDll_x64
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


# add_executable(DobotServer src/DobotServer.cpp)
# target_link_libraries(DobotServer ${catkin_LIBRARIES} DobotDll)
# add_dependencies(DobotServer dobot_gencpp)

# add_executable(DobotClient_JOG src/DobotClient_JOG.cpp)
# target_link_libraries(DobotClient_JOG ${catkin_LIBRARIES})
# add_dependencies(DobotClient_JOG dobot_gencpp)

# add_executable(DobotClient_PTP src/DobotClient_PTP.cpp)
# target_link_libraries(DobotClient_PTP ${catkin_LIBRARIES})
# add_dependencies(DobotClient_PTP dobot_gencpp)
