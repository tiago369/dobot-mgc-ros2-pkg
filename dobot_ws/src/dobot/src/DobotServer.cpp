// #include "ros/ros.h"
#include "rclcpp/rclcpp.hpp"
// #include "std_msgs/String.h"
#include "std_msgs/msg/string.hpp"
// #include "std_msgs/Float32MultiArray.h"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "DobotDllx64/DobotDll.h"

/*
 * Cmd timeout
 */
// #include "dobot/SetCmdTimeout.h"
#include "dobot/srv/set_cmd_timeout.hpp"
// 1 function
void SetCmdTimeoutService(const std::shared_ptr<dobot::srv::SetCmdTimeout::Request> req, 
                                std::shared_ptr<dobot::srv::SetCmdTimeout::Response> res)
{
    res.result = SetCmdTimeout(req.timeout);

    // return true;
}

void InitCmdTimeoutServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/SetCmdTimeout", SetCmdTimeoutService);
    serverVec.push_back(server);
}

/*
 * Device information
 */
// #include "dobot/GetDeviceSN.h"
#include "dobot/srv/get_device_sn.hpp"
// #include "dobot/SetDeviceName.h"
#include "dobot/srv/set_device_name.hpp"
// #include "dobot/GetDeviceName.h"
#include "dobot/srv/get_device_dame.hpp"
// #include "dobot/GetDeviceVersion.h"
#include "dobot/srv/get_device_version.hpp"

// 2 function
void GetDeviceSNService(const std::shared_ptr<dobot::srv::GetDeviceSN::Request> req, 
                              std::shared_ptr<dobot::GetDeviceSN::Response> res)
{
    char device_sn[256];

    res.result = GetDeviceSN(device_sn, sizeof(device_sn));
    if (res.result == DobotCommunicate_NoError) {
        std::stringstream ss;
        ss << device_sn;
        res.device_sn.data = ss.str();
    }

    // return true;
}

// 3 function
void SetDeviceNameService(const std::shared_ptr<dobot::srv::SetDeviceName::Request> req, 
                                std::shared_ptr<dobot::srv::SetDeviceName::Response> res)
{
    res.result = SetDeviceName(req.device_name.data.c_str());

    // return true;
}

// 4 function
void GetDeviceNameService(const std::shared_ptr<dobot::srv::GetDeviceName::Request> req, 
                                std::shared_ptr<dobot::srv::GetDeviceName::Response> res)
{
    char device_name[256];

    res.result = GetDeviceName(device_name, sizeof(device_name));
    if (res.result == DobotCommunicate_NoError) {
        std::stringstream ss;
        ss << device_name;
        res.device_name.data = ss.str();
    }

    // return true;
}

// 5 function
void GetDeviceVersionService(const std::shared_ptr<dobot::srv::GetDeviceVersion::Request> req, 
                                    std::shared_ptr<dobot::srv::GetDeviceVersion::Response> res)
{
    uint8_t major_version, minor_version, revision;

    res.result = GetDeviceVersion(&major_version, &minor_version, &revision);
    if (res.result == DobotCommunicate_NoError) {
        res.major_version = major_version;
        res.minor_version = minor_version;
        res.revision = revision;
    }

    // return true;
}

void InitDeviceInfoServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/GetDeviceSN", GetDeviceSNService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetDeviceName", SetDeviceNameService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetDeviceName", GetDeviceNameService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetDeviceVersion", GetDeviceVersionService);
    serverVec.push_back(server);
}

/*
 * Pose
 */

// 6 function
// #include "dobot/GetPose.h"
#include "dobot/srv/get_pose.hpp"

void GetPoseService(const std::shared_ptr<dobot::GetPose::Request> req, 
                          std::shared_ptr<dobot::GetPose::Response> res)
{
    Pose pose;

    res.result = GetPose(&pose);
    if (res.result == DobotCommunicate_NoError) {
        res.x = pose.x;
        res.y = pose.y;
        res.z = pose.z;
        res.r = pose.r;
        for (int i = 0; i < 4; i++) {
            res.joint_angle.push_back(pose.joint_angle[i]);
        }
    }

    // return true;
}

void InitPoseServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/GetPose", GetPoseService);
    serverVec.push_back(server);
}

/*
 * Alarms
 */
// #include "dobot/GetAlarmsState.h"
#include "dobot/srv/get_alarms_state.hpp"
// #include "dobot/ClearAllAlarmsState.h"
#include "dobot/srv/clear_all_alarms_state.hpp"
// 7 function
void GetAlarmsStateService(const std::shared_ptr<dobot::srv::GetAlarmsState::Request> req, 
                                std::shared_ptr<dobot::srv::GetAlarmsState::Response> res)
{
    uint8_t alarms_state[128];
    uint32_t len;

    res.result = GetAlarmsState(alarms_state, &len, sizeof(alarms_state));
    if (res.result == DobotCommunicate_NoError) {
        for (int i = 0; i < len; i++) {
            res.alarms_state.push_back(alarms_state[i]);
        }
    }

    // return true;
}

// 8 function
void ClearAllAlarmsStateService(const std::shared_ptr<dobot::srv::ClearAllAlarmsState::Request> req, 
                                      std::shared_ptr<dobot::srv::ClearAllAlarmsState::Response> res)
{
    res.result = ClearAllAlarmsState();

    // return true;
}

void InitAlarmsServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/GetAlarmsState", GetAlarmsStateService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/ClearAllAlarmsState", ClearAllAlarmsStateService);
    serverVec.push_back(server);
}

/*
 * HOME
 */
// #include "dobot/SetHOMEParams.h"
#include "dobot/srv/set_home_params.hpp"
// #include "dobot/GetHOMEParams.h"
#include "dobot/srv/get_home_params.hpp"
// #include "dobot/SetHOMECmd.h"
#include "dobot/srv/set_home_cmd.hpp"

// 9 function
void SetHOMEParamsService(const std::shared_ptr<dobot::srv::SetHOMEParams::Request> req, 
                                std::shared_ptr<dobot::srv::SetHOMEParams::Response> res)
{
    HOMEParams params;
    uint64_t queued_cmd_index;

    params.x = req.x;
    params.y = req.y;
    params.z = req.z;
    params.r = req.r;

    res.result = SetHOMEParams(&params, req.is_queued, &queued_cmd_index);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queued_cmd_index;
    }

    // return true;
}

// 10 function
void GetHOMEParamsService(const std::shared_ptr<dobot::srv::GetHOMEParams::Request> req, 
                                std::shared_ptr<dobot::srv::GetHOMEParams::Response> res)
{
    HOMEParams params;

    res.result = GetHOMEParams(&params);
    if (res.result == DobotCommunicate_NoError) {
        res.x = params.x;
        res.y = params.y;
        res.z = params.z;
        res.r = params.r;
    }

    // return true;
}

// 11 function
void SetHOMECmdService(const std::shared_ptr<dobot::srv::SetHOMECmd::Request> req, 
                             std::shared_ptr<dobot::srv::SetHOMECmd::Response> res)
{
    HOMECmd cmd;
    uint64_t queued_cmd_index;

    res.result = SetHOMECmd(&cmd, true, &queued_cmd_index);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queued_cmd_index;
    }

    // return true;
}

void InitHOMEServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/SetHOMEParams", SetHOMEParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetHOMEParams", GetHOMEParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetHOMECmd", SetHOMECmdService);
    serverVec.push_back(server);
}

/*
 * End effector
 */
// #include "dobot/SetEndEffectorParams.h"
#include "dobot/srv/set_end_effector_params.hpp"
// #include "dobot/GetEndEffectorParams.h"
#include "dobot/srv/get_end_effector_params.hpp"
// #include "dobot/SetEndEffectorLaser.h"
#include "dobot/srv/set_end_effector_laser.hpp"
// #include "dobot/GetEndEffectorLaser.h"
#include "dobot/srv/get_end_effector_laser.h"
// #include "dobot/SetEndEffectorSuctionCup.h"
#include "dobot/srv/set_end_effector_suction_cup.hpp"
// #include "dobot/GetEndEffectorSuctionCup.h"
#include "dobot/srv/get_end_effector_suction_cup.hpp"
// #include "dobot/SetEndEffectorGripper.h"
#include "dobot/srv/set_end_effector_gripper.hpp"
// #include "dobot/GetEndEffectorGripper.h"
#include "dobot/srv/get_end_effector_gripper.hpp"

// 12 function
void SetEndEffectorParamsService(const std::shared_ptr<dobot::srv::SetEndEffectorParams::Request> req,
                                        std::shared_ptr<dobot::srv::SetEndEffectorParams::Response> res)
{
    EndEffectorParams params;
    uint64_t queued_cmd_index;

    params.x_bias = req.x_bias;
    params.y_bias = req.y_bias;
    params.z_bias = req.z_bias;

    res.result = SetEndEffectorParams(&params, req.is_queued, &queued_cmd_index);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queued_cmd_index;
    }

    // return true;
}

//13 function
void GetEndEffectorParamsService(const std::shared_ptr<dobot::srv::GetEndEffectorParams::Request> req,
                                        std::shared_ptr<dobot::srv::GetEndEffectorParams::Response> res)
{
    EndEffectorParams params;

    res.result = GetEndEffectorParams(&params);
    if (res.result == DobotCommunicate_NoError) {
        res.x_bias = params.xBias;
        res.y_bias = params.yBias;
        res.z_bias = params.zBias;
    }

    // return true;
}

// 14 function
void SetEndEffectorLaserService(const std::shared_ptr<dobot::srv::SetEndEffectorLaser::Request> req, 
                                      std::shared_ptr<dobot::srv::SetEndEffectorLaser::Response> res)
{
    uint64_t queuedCmdIndex;

    res.result = SetEndEffectorLaser(req.enable_ctrl, req.on, req.is_queued, &queued_cmd_index);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 15 function
void GetEndEffectorLaserService(const std::shared_ptr<dobot::srv::GetEndEffectorLaser::Request> req, 
                                      std::shared_ptr<dobot::srv::GetEndEffectorLaser::Response> res)
{
    bool enableCtrl, on;

    res.result = GetEndEffectorLaser(&enableCtrl, &on);
    if (res.result == DobotCommunicate_NoError) {
        res.enable_ctrl = enableCtrl;
        res.on = on;
    }

    // return true;
}

// 16 function  
void SetEndEffectorSuctionCupService(const std::shared_ptr<dobot::srv::SetEndEffectorSuctionCup::Request> req, 
                                           std::shared_ptr<dobot::srv::SetEndEffectorSuctionCup::Response> res)
{
    uint64_t queuedCmdIndex;

    res.result = SetEndEffectorSuctionCup(req.enable_ctrl, req.suck, req.is_queued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 17 function 
void GetEndEffectorSuctionCupService(const std::shared_ptr<dobot::srv::GetEndEffectorSuctionCup::Request> req, 
                                           std::shared_ptr<dobot::srv::GetEndEffectorSuctionCup::Response> res)
{
    bool enableCtrl, suck;

    res.result = GetEndEffectorLaser(&enableCtrl, &suck);
    if (res.result == DobotCommunicate_NoError) {
        res.enable_ctrl = enableCtrl;
        res.suck = suck;
    }

    // return true;
}

// 18 function
void SetEndEffectorGripperService(const std::shared_ptr<dobot::srv::SetEndEffectorGripper::Request> req, 
                                        std::shared_ptr<dobot::srv::SetEndEffectorGripper::Response> res)
{
    uint64_t queuedCmdIndex;

    res.result = SetEndEffectorGripper(req.enable_ctrl, req.grip, req.is_queued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 19 function
void GetEndEffectorGripperService(const std::shared_ptr<dobot::srv::GetEndEffectorGripper::Request> req, 
                                        std::shared_ptr<dobot::srv::GetEndEffectorGripper::Response> res)
{
    bool enableCtrl, grip;

    res.result = GetEndEffectorLaser(&enableCtrl, &grip);
    if (res.result == DobotCommunicate_NoError) {
        res.enable_ctrl = enableCtrl;
        res.grip = grip;
    }

    // return true;
}

void InitEndEffectorServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/SetEndEffectorParams", SetEndEffectorParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetEndEffectorParams", GetEndEffectorParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetEndEffectorLaser", SetEndEffectorLaserService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetEndEffectorLaser", GetEndEffectorLaserService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetEndEffectorSuctionCup", SetEndEffectorSuctionCupService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetEndEffectorSuctionCup", GetEndEffectorSuctionCupService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetEndEffectorGripper", SetEndEffectorGripperService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetEndEffectorGripper", GetEndEffectorGripperService);
    serverVec.push_back(server);
}

/*
 * JOG
 */
// #include "dobot/SetJOGJointParams.h"
#include "dobot/srv/set_jog_joint_params.hpp"
// #include "dobot/GetJOGJointParams.h"
#include "dobot/srv/get_jog_joint_params.hpp"
// #include "dobot/SetJOGCoordinateParams.h"
#include "dobot/srv/set_jog_coordinate_params.hpp"
// #include "dobot/GetJOGCoordinateParams.h"
#include "dobot/srv/get_jog_coordinate_params.hpp"
// #include "dobot/SetJOGCommonParams.h"
#include "dobot/srv/set_jog_common_params.hpp"
// #include "dobot/GetJOGCommonParams.h"
#include "dobot/srv/get_jog_common_params.hpp"
// #include "dobot/SetJOGCmd.h"
#include "dobot/srv/set_jog_cmd.hpp"

// 20 function 
void SetJOGJointParamsService(const std::shared_ptr<dobot::srv::SetJOGJointParams::Request> req, 
                                    std::shared_ptr<dobot::srv::SetJOGJointParams::Response> res)
{
    JOGJointParams params;
    uint64_t queuedCmdIndex;

    for (int i = 0; i < req.velocity.size(); i++) {
        params.velocity[i] = req.velocity[i];
    }
    for (int i = 0; i < req.acceleration.size(); i++) {
        params.acceleration[i] = req.acceleration[i];
    }
    res.result = SetJOGJointParams(&params, req.is_queued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 21 function
void GetJOGJointParamsService(const std::shared_ptr<dobot::srv::GetJOGJointParams::Request> req, 
                                    std::shared_ptr<dobot::srv::GetJOGJointParams::Response> res)
{
    JOGJointParams params;

    res.result = GetJOGJointParams(&params);
    if (res.result == DobotCommunicate_NoError) {
        for (int i = 0; i < 4; i++) {
            res.velocity.push_back(params.velocity[i]);
            res.acceleration.push_back(params.acceleration[i]);
        }
    }

    // return true;
}

// 22 function
void SetJOGCoordinateParamsService(const std::shared_ptr<dobot::srv::SetJOGCoordinateParams::Request> req, 
                                         std::shared_ptr<dobot::srv::SetJOGCoordinateParams::Response> res)
{
    JOGCoordinateParams params;
    uint64_t queuedCmdIndex;

    for (int i = 0; i < req.velocity.size(); i++) {
        params.velocity[i] = req.velocity[i];
    }
    for (int i = 0; i < req.acceleration.size(); i++) {
        params.acceleration[i] = req.acceleration[i];
    }
    res.result = SetJOGCoordinateParams(&params, req.is_queued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 23 function
void GetJOGCoordinateParamsService(const std::shared_ptr<dobot::srv::GetJOGCoordinateParams::Request> req, 
                                         std::shared_ptr<dobot::srv::GetJOGCoordinateParams::Response> res)
{
    JOGCoordinateParams params;

    res.result = GetJOGCoordinateParams(&params);
    if (res.result == DobotCommunicate_NoError) {
        for (int i = 0; i < 4; i++) {
            res.velocity.push_back(params.velocity[i]);
            res.acceleration.push_back(params.acceleration[i]);
        }
    }

    // return true;
}

// 24 function
void SetJOGCommonParamsService(const std::shared_ptr<dobot::srv::SetJOGCommonParams::Request> req, 
                                     std::shared_ptr<dobot::srv::SetJOGCommonParams::Response> res)
{
    JOGCommonParams params;
    uint64_t queuedCmdIndex;

    params.velocityRatio = req.velocity_ratio;
    params.accelerationRatio = req.acceleration_ratio;
    res.result = SetJOGCommonParams(&params, req.is_queued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 25 function
void GetJOGCommonParamsService(const std::shared_ptr<dobot::srv::GetJOGCommonParams::Request> req, 
                                     std::shared_ptr<dobot::srv::GetJOGCommonParams::Response> res)
{
    JOGCommonParams params;

    res.result = GetJOGCommonParams(&params);
    if (res.result == DobotCommunicate_NoError) {
        res.velocity_ratio = params.velocityRatio;
        res.acceleration_ratio = params.accelerationRatio;
    }

    // return true;
}

// 26 function
void SetJOGCmdService(const std::shared_ptr<dobot::srv::SetJOGCmd::Request> req, 
                            std::shared_ptr<dobot::srv::SetJOGCmd::Response> res)
{
    JOGCmd cmd;
    uint64_t queuedCmdIndex;

    cmd.isJoint = req.is_joint;
    cmd.cmd = req.cmd;
    res.result = SetJOGCmd(&cmd, false, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

void InitJOGServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/SetJOGJointParams", SetJOGJointParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetJOGJointParams", GetJOGJointParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetJOGCoordinateParams", SetJOGCoordinateParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetJOGCoordinateParams", GetJOGCoordinateParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetJOGCommonParams", SetJOGCommonParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetJOGCommonParams", GetJOGCommonParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetJOGCmd", SetJOGCmdService);
    serverVec.push_back(server);
}

/*
 * PTP
 */
// #include "dobot/SetPTPJointParams.h"
#include "dobot/srv/set_ptp_joint_params.hpp"
// #include "dobot/GetPTPJointParams.h"
#include "dobot/srv/get_ptp_joint_params.hpp"
// #include "dobot/SetPTPCoordinateParams.h"
#include "dobot/srv/set_ptp_coordinate_params.hpp"
// #include "dobot/GetPTPCoordinateParams.h"
#include "dobot/srv/get_ptp_coordinate_params.hpp"
// #include "dobot/SetPTPJumpParams.h"
#include "dobot/srv/set_ptp_jump_params.hpp"
// #include "dobot/GetPTPJumpParams.h"
#include "dobot/srv/get_ptp_jump_params.hpp"
// #include "dobot/SetPTPCommonParams.h"
#include "dobot/srv/set_ptp_common_params.hpp"
// #include "dobot/GetPTPCommonParams.h"
#include "dobot/srv/get_ptp_common_params.hpp"
// #include "dobot/SetPTPCmd.h"
#include "dobot/srv/set_ptp_cmd.hpp"

// 27 function 
void SetPTPJointParamsService(const std::shared_ptr<dobot::srv::SetPTPJointParams::Request> req, 
                                    std::shared_ptr<dobot::srv::SetPTPJointParams::Response> res)
{
    PTPJointParams params;
    uint64_t queuedCmdIndex;

    for (int i = 0; i < req.velocity.size(); i++) {
        params.velocity[i] = req.velocity[i];
    }
    for (int i = 0; i < req.acceleration.size(); i++) {
        params.acceleration[i] = req.acceleration[i];
    }
    res.result = SetPTPJointParams(&params, req.is_queued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 28 function 
void GetPTPJointParamsService(const std::shared_ptr<dobot::srv::GetPTPJointParams::Request> req, 
                                    std::shared_ptr<dobot::srv::GetPTPJointParams::Response> res)
{
    PTPJointParams params;

    res.result = GetPTPJointParams(&params);
    if (res.result == DobotCommunicate_NoError) {
        for (int i = 0; i < 4; i++) {
            res.velocity.push_back(params.velocity[i]);
            res.acceleration.push_back(params.acceleration[i]);
        }
    }

    // return true;
}

// 29 function 
void SetPTPCoordinateParamsService(const std::shared_ptr<dobot::srv::SetPTPCoordinateParams::Request> req, 
                                         std::shared_ptr<dobot::srv::SetPTPCoordinateParams::Response> res)
{
    PTPCoordinateParams params;
    uint64_t queuedCmdIndex;

    params.xyzVelocity = req.xyz_velocity;
    params.rVelocity = req.r_velocity;
    params.xyzAcceleration = req.xyz_acceleration;
    params.rAcceleration = req.r_acceleration;
    res.result = SetPTPCoordinateParams(&params, req.is_queued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 30 function
void GetPTPCoordinateParamsService(const std::shared_ptr<dobot::srv::GetPTPCoordinateParams::Request> req, 
                                         std::shared_ptr<dobot::srv::GetPTPCoordinateParams::Response> res)
{
    PTPCoordinateParams params;

    res.result = GetPTPCoordinateParams(&params);
    if (res.result == DobotCommunicate_NoError) {
        res.xyz_velocity = params.xyzVelocity;
        res.r_velocity = params.rVelocity;
        res.xyz_acceleration = params.xyzAcceleration;
        res.r_acceleration = params.rAcceleration;
    }

    // return true;
}

// 31 function
void SetPTPJumpParamsService(const std::shared_ptr<dobot::srv::SetPTPJumpParams::Request> req, 
                                   std::shared_ptr<dobot::srv::SetPTPJumpParams::Response> res)
{
    PTPJumpParams params;
    uint64_t queuedCmdIndex;

    params.jumpHeight = req.jump_height;
    params.zLimit = req.z_limit;
    res.result = SetPTPJumpParams(&params, req.is_queued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 32 function
void GetPTPJumpParamsService(const std::shared_ptr<dobot::srv::GetPTPJumpParams::Request> req, 
                                   std::shared_ptr<dobot::srv::GetPTPJumpParams::Response> res)
{
    PTPJumpParams params;

    res.result = GetPTPJumpParams(&params);
    if (res.result == DobotCommunicate_NoError) {
        res.jump_height = params.jumpHeight;
        res.z_limit = params.zLimit;
    }

    // return true;
}

// 33 function 
void SetPTPCommonParamsService(const std::shared_ptr<dobot::srv::SetPTPCommonParams::Request> req, 
                                     std::shared_ptr<dobot::srv::SetPTPCommonParams::Response> res)
{
    PTPCommonParams params;
    uint64_t queuedCmdIndex;

    params.velocityRatio = req.velocity_ratio;
    params.accelerationRatio = req.acceleration_ratio;
    res.result = SetPTPCommonParams(&params, req.is_queued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 34 function
void GetPTPCommonParamsService(const std::shared_ptr<dobot::srv::GetPTPCommonParams::Request> req, 
                                    std::shared_ptr<dobot::srv::GetPTPCommonParams::Response> res)
{
    PTPCommonParams params;

    res.result = GetPTPCommonParams(&params);
    if (res.result == DobotCommunicate_NoError) {
        res.velocity_ratio = params.velocityRatio;
        res.acceleration_ratio = params.accelerationRatio;
    }

    // return true;
}

// 35 function
void SetPTPCmdService(const std::shared_ptr<dobot::srv::SetPTPCmd::Request> req, 
                            std::shared_ptr<dobot::srv::SetPTPCmd::Response> res)
{
    PTPCmd cmd;
    uint64_t queuedCmdIndex;

    cmd.ptpMode = req.ptp_mode;
    cmd.x = req.x;
    cmd.y = req.y;
    cmd.z = req.z;
    cmd.r = req.r;
    res.result = SetPTPCmd(&cmd, true, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

void InitPTPServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/SetPTPJointParams", SetPTPJointParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetPTPJointParams", GetPTPJointParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetPTPCoordinateParams", SetPTPCoordinateParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetPTPCoordinateParams", GetPTPCoordinateParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetPTPJumpParams", SetPTPJumpParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetPTPJumpParams", GetPTPJumpParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetPTPCommonParams", SetPTPCommonParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetPTPCommonParams", GetPTPCommonParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetPTPCmd", SetPTPCmdService);
    serverVec.push_back(server);
}

/*
 * CP
 */
// #include "dobot/SetCPParams.h"
#include "dobot/srv/set_cp_params.hpp"
// #include "dobot/GetCPParams.h"
#include "dobot/srv/get_cp_params.hpp"
// #include "dobot/SetCPCmd.h"
#include "dobot/srv/set_cp_cmd.hpp"

// 36 function
void SetCPParamsService(const std::shared_ptr<dobot::srv::SetCPParams::Request> req, 
                              std::shared_ptr<dobot::srv::SetCPParams::Response> res)
{
    CPParams params;
    uint64_t queuedCmdIndex;

    params.planAcc = req.plan_acc;
    params.juncitionVel = req.junction_vel;
    params.acc = req.acc;
    params.realTimeTrack = req.real_time_track;
    res.result = SetCPParams(&params, req.is_queued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 37 function
void GetCPParamsService(const std::shared_ptr<dobot::srv::GetCPParams::Request> req, 
                              std::shared_ptr<dobot::srv::GetCPParams::Response> res)
{
    CPParams params;

    res.result = GetCPParams(&params);
    if (res.result == DobotCommunicate_NoError) {
        res.plan_acc = params.planAcc;
        res.junction_vel = params.juncitionVel;
        res.acc = params.acc;
        res.real_time_track = params.realTimeTrack;
    }

    // return true;
}

// 38 function
void SetCPCmdService(const std::shared_ptr<dobot::srv::etCPCmd::Request> req, 
                           std::shared_ptr<dobot::srv::SetCPCmd::Response> res)
{
    CPCmd cmd;
    uint64_t queuedCmdIndex;

    cmd.cpMode = req.cp_mode;
    cmd.x = req.x;
    cmd.y = req.y;
    cmd.z = req.z;
    cmd.velocity = req.velocity;

    res.result = SetCPCmd(&cmd, true, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

void InitCPServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/SetCPParams", SetCPParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetCPParams", GetCPParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetCPCmd", SetCPCmdService);
    serverVec.push_back(server);
}

/*
 * ARC
 */
// #include "dobot/SetARCParams.h"
#include "dobot/srv/set_arc_params.hpp"
// #include "dobot/GetARCParams.h"
#include "dobot/srv/get_arc_params.hpp"
#include "dobot/SetARCCmd.h"

// 39 function
void SetARCParamsService(const std::shared_ptr<dobot::srv::SetARCParams::Request> req, 
                               std::shared_ptr<dobot::srv::SetARCParams::Response> res)
{
    ARCParams params;
    uint64_t queuedCmdIndex;

    params.xyzVelocity = req.xyz_velocity;
    params.rVelocity = req.r_velocity;
    params.xyzAcceleration = req.xyz_acceleration;
    params.rAcceleration = req.r_acceleration;
    res.result = SetARCParams(&params, req.is_queued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queued_cmd_index = queuedCmdIndex;
    }

    // return true;
}

// 40 function
void GetARCParamsService(const std::shared_ptr<dobot::srv::GetARCParams::Request> req, 
                               std::shared_ptr<dobot::srv::GetARCParams::Response> res)
{
    ARCParams params;

    res.result = GetARCParams(&params);
    if (res.result == DobotCommunicate_NoError) {
        res.xyz_velocity = params.xyzVelocity;
        res.r_velocity = params.rVelocity;
        res.xyz_acceleration = params.xyzAcceleration;
        res.r_acceleration = params.rAcceleration;
    }

    // return true;
}

bool SetARCCmdService(dobot::SetARCCmd::Request &req, dobot::SetARCCmd::Response &res)
{
    ARCCmd cmd;
    uint64_t queuedCmdIndex;

    cmd.cirPoint.x = req.x1;
    cmd.cirPoint.y = req.y1;
    cmd.cirPoint.z = req.z1;
    cmd.cirPoint.r = req.r1;
    cmd.toPoint.x = req.x2;
    cmd.toPoint.y = req.y2;
    cmd.toPoint.z = req.z2;
    cmd.toPoint.r = req.r2;

    res.result = SetARCCmd(&cmd, true, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queuedCmdIndex = queuedCmdIndex;
    }

    return true;
}

void InitARCServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/SetARCParams", SetARCParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetARCParams", GetARCParamsService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetARCCmd", SetARCCmdService);
    serverVec.push_back(server);
}

/*
 * WAIT
 */
#include "dobot/SetWAITCmd.h"

bool SetWAITCmdService(dobot::SetWAITCmd::Request &req, dobot::SetWAITCmd::Response &res)
{
    WAITCmd cmd;
    uint64_t queuedCmdIndex;

    cmd.timeout = req.timeout;
    res.result = SetWAITCmd(&cmd, true, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queuedCmdIndex = queuedCmdIndex;
    }

    return true;
}

void InitWAITServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/SetWAITCmd", SetWAITCmdService);
    serverVec.push_back(server);
}

/*
 * TRIG
 */
#include "dobot/SetTRIGCmd.h"

bool SetTRIGCmdService(dobot::SetTRIGCmd::Request &req, dobot::SetTRIGCmd::Response &res)
{
    TRIGCmd cmd;
    uint64_t queuedCmdIndex;

    cmd.address = req.address;
    cmd.mode = req.mode;
    cmd.condition = req.condition;
    cmd.threshold = req.threshold;
    res.result = SetTRIGCmd(&cmd, true, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queuedCmdIndex = queuedCmdIndex;
    }

    return true;
}

void InitTRIGServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/SetTRIGCmd", SetTRIGCmdService);
    serverVec.push_back(server);
}

/*
 * EIO
 */
#include "dobot/SetIOMultiplexing.h"
#include "dobot/GetIOMultiplexing.h"
#include "dobot/SetIODO.h"
#include "dobot/GetIODO.h"
#include "dobot/SetIOPWM.h"
#include "dobot/GetIOPWM.h"
#include "dobot/GetIODI.h"
#include "dobot/GetIOADC.h"
#include "dobot/SetEMotor.h"
#include "dobot/SetInfraredSensor.h"
#include "dobot/GetInfraredSensor.h"
#include "dobot/SetColorSensor.h"
#include "dobot/GetColorSensor.h"

bool SetIOMultiplexingService(dobot::SetIOMultiplexing::Request &req, dobot::SetIOMultiplexing::Response &res)
{
    IOMultiplexing ioMultiplexing;
    uint64_t queuedCmdIndex;

    ioMultiplexing.address = req.address;
    ioMultiplexing.multiplex = req.multiplex;
    res.result = SetIOMultiplexing(&ioMultiplexing, req.isQueued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queuedCmdIndex = queuedCmdIndex;
    }

    return true;
}

bool GetIOMultiplexingService(dobot::GetIOMultiplexing::Request &req, dobot::GetIOMultiplexing::Response &res)
{
    IOMultiplexing ioMultiplexing;

    ioMultiplexing.address = req.address;
    res.result = GetIOMultiplexing(&ioMultiplexing);
    if (res.result == DobotCommunicate_NoError) {
        res.multiplex = ioMultiplexing.multiplex;
    }

    return true;
}

bool SetIODOService(dobot::SetIODO::Request &req, dobot::SetIODO::Response &res)
{
    IODO ioDO;
    uint64_t queuedCmdIndex;

    ioDO.address = req.address;
    ioDO.level = req.level;
    res.result = SetIODO(&ioDO, req.isQueued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queuedCmdIndex = queuedCmdIndex;
    }

    return true;
}

bool GetIODOService(dobot::GetIODO::Request &req, dobot::GetIODO::Response &res)
{
    IODO ioDO;

    ioDO.address = req.address;
    res.result = GetIODO(&ioDO);
    if (res.result == DobotCommunicate_NoError) {
        res.level = ioDO.level;
    }

    return true;
}

bool SetIOPWMService(dobot::SetIOPWM::Request &req, dobot::SetIOPWM::Response &res)
{
    IOPWM ioPWM;
    uint64_t queuedCmdIndex;

    ioPWM.address = req.address;
    ioPWM.frequency = req.frequency;
    ioPWM.dutyCycle = req.dutyCycle;
    res.result = SetIOPWM(&ioPWM, req.isQueued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queuedCmdIndex = queuedCmdIndex;
    }

    return true;
}

bool GetIOPWMService(dobot::GetIOPWM::Request &req, dobot::GetIOPWM::Response &res)
{
    IOPWM ioPWM;

    ioPWM.address = req.address;
    res.result = GetIOPWM(&ioPWM);
    if (res.result == DobotCommunicate_NoError) {
        res.frequency = ioPWM.frequency;
        res.dutyCycle = ioPWM.dutyCycle;
    }

    return true;
}

bool GetIODIService(dobot::GetIODI::Request &req, dobot::GetIODI::Response &res)
{
    IODI ioDI;

    ioDI.address = req.address;
    res.result = GetIODI(&ioDI);
    if (res.result == DobotCommunicate_NoError) {
        res.level = ioDI.level;
    }

    return true;
}

bool GetIOADCService(dobot::GetIOADC::Request &req, dobot::GetIOADC::Response &res)
{
    IOADC ioADC;

    ioADC.address = req.address;
    res.result = GetIOADC(&ioADC);
    if (res.result == DobotCommunicate_NoError) {
        res.value = ioADC.value;
    }

    return true;
}

bool SetEMotorService(dobot::SetEMotor::Request &req, dobot::SetEMotor::Response &res)
{
    EMotor eMotor;
    uint64_t queuedCmdIndex;

    eMotor.index = req.index;
    eMotor.isEnabled = req.isEnabled;
    eMotor.speed = req.speed;
    res.result = SetEMotor(&eMotor, req.isQueued, &queuedCmdIndex);
    if (res.result == DobotCommunicate_NoError) {
        res.queuedCmdIndex = queuedCmdIndex;
    }

    return true;
}


bool SetInfraredSensorService(dobot::SetInfraredSensor::Request &req, dobot::SetInfraredSensor::Response &res)
{
    InfraredPort infraredPort = InfraredPort(req.infraredPort);
    res.result = SetInfraredSensor(req.enableCtrl, infraredPort);

    return true;
}

bool GetInfraredSensorService(dobot::GetInfraredSensor::Request &req, dobot::GetInfraredSensor::Response &res)
{
    uint8_t value;
    InfraredPort infraredPort = InfraredPort(req.infraredPort);
    res.result = GetInfraredSensor(infraredPort, &value);
    if (res.result == DobotCommunicate_NoError) {
        res.value = value;
    }

    return true;
}

bool SetColorSensorService(dobot::SetColorSensor::Request &req, dobot::SetColorSensor::Response &res)
{
    ColorPort colorPort = ColorPort(req.colorPort);
    res.result = SetColorSensor(req.enableCtrl, colorPort);

    return true;
}

bool GetColorSensorService(dobot::GetColorSensor::Request &req, dobot::GetColorSensor::Response &res)
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    res.result = GetColorSensor(&r, &g, &b);
    if (res.result == DobotCommunicate_NoError) {
        res.r = r;
        res.g = g;
        res.b = b;
    }

    return true;
}

void InitEIOServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/SetIOMultiplexing", SetIOMultiplexingService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetIOMultiplexing", GetIOMultiplexingService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetIODO", SetIODOService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetIODO", GetIODOService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetIOPWM", SetIOPWMService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetIOPWM", GetIOPWMService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetIODI", GetIODIService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetIOADC", GetIOADCService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetEMotor", SetEMotorService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetInfraredSensor", SetInfraredSensorService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetInfraredSensor", GetInfraredSensorService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetColorSensor", SetColorSensorService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/GetColorSensor", GetColorSensorService);
    serverVec.push_back(server);
}

/*
 * Queued command control
 */
#include "dobot/SetQueuedCmdStartExec.h"
#include "dobot/SetQueuedCmdStopExec.h"
#include "dobot/SetQueuedCmdForceStopExec.h"
#include "dobot/SetQueuedCmdClear.h"

bool SetQueuedCmdStartExecService(dobot::SetQueuedCmdStartExec::Request &req, dobot::SetQueuedCmdStartExec::Response &res)
{
    res.result = SetQueuedCmdStartExec();

    return true;
}

bool SetQueuedCmdStopExecService(dobot::SetQueuedCmdStopExec::Request &req, dobot::SetQueuedCmdStopExec::Response &res)
{
    res.result = SetQueuedCmdStopExec();

    return true;
}

bool SetQueuedCmdForceStopExecService(dobot::SetQueuedCmdForceStopExec::Request &req, dobot::SetQueuedCmdForceStopExec::Response &res)
{
    res.result = SetQueuedCmdForceStopExec();

    return true;
}

bool SetQueuedCmdClearService(dobot::SetQueuedCmdClear::Request &req, dobot::SetQueuedCmdClear::Response &res)
{
    res.result = SetQueuedCmdClear();

    return true;
}

void InitQueuedCmdServices(ros::NodeHandle &n, std::vector<ros::ServiceServer> &serverVec)
{
    ros::ServiceServer server;

    server = n.advertiseService("/DobotServer/SetQueuedCmdStartExec", SetQueuedCmdStartExecService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetQueuedCmdStopExec", SetQueuedCmdStopExecService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetQueuedCmdForceStopExec", SetQueuedCmdForceStopExecService);
    serverVec.push_back(server);
    server = n.advertiseService("/DobotServer/SetQueuedCmdClear", SetQueuedCmdClearService);
    serverVec.push_back(server);
}





int main(int argc, char **argv)
{
    if (argc < 2) {
        ROS_ERROR("[USAGE]Application portName");
        return -1;
    }
    // Connect Dobot before start the service
    int result = ConnectDobot(argv[1], 115200, 0, 0);
    switch (result) {
        case DobotConnect_NoError:
        break;
        case DobotConnect_NotFound:
            ROS_ERROR("Dobot not found!");
            return -2;
        break;
        case DobotConnect_Occupied:
            ROS_ERROR("Invalid port name or Dobot is occupied by other application!");
            return -3;
        break;
        default:
        break;
    }
    ros::init(argc, argv, "DobotServer");
    ros::NodeHandle n;

    std::vector<ros::ServiceServer> serverVec;

    InitCmdTimeoutServices(n, serverVec);
    InitDeviceInfoServices(n, serverVec);
    InitPoseServices(n, serverVec);
    InitAlarmsServices(n, serverVec);
    InitHOMEServices(n, serverVec);
    InitEndEffectorServices(n, serverVec);
    InitJOGServices(n, serverVec);
    InitPTPServices(n, serverVec);
    InitCPServices(n, serverVec);
    InitARCServices(n, serverVec);
    InitWAITServices(n, serverVec);
    InitTRIGServices(n, serverVec);
    InitEIOServices(n, serverVec);
    InitQueuedCmdServices(n, serverVec);

    ROS_INFO("Dobot service running...");
    ros::spin();
    ROS_INFO("Dobot service exiting...");

    // Disconnect Dobot
    DisconnectDobot();

    return 0;
}

