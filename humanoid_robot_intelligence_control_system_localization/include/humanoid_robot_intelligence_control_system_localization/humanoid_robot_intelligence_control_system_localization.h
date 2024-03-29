/*******************************************************************************
 * Copyright 2018 ROBOTIS CO., LTD.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

/* Author: SCH */

#ifndef HUMANOID_ROBOT_LOCALIZATION_H_
#define HUMANOID_ROBOT_LOCALIZATION_H_

// std
#include <string>

// ros dependencies
#include <ros/ros.h>

// ros msg, srv
#include <eigen_conversions/eigen_msg.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Int16.h>
#include <std_msgs/String.h>
#include <tf/transform_broadcaster.h>

// eigen
#include <eigen3/Eigen/Eigen>

// boost
#include <boost/thread.hpp>

#include "humanoid_robot_intelligence_control_system_math/humanoid_robot_intelligence_control_system_math.h"

namespace humanoid_robot_intelligence_control_system_op {

class HUMANOID_ROBOTLocalization {

private:
  // ros node handle
  ros::NodeHandle ros_node_;

  // subscriber
  ros::Subscriber pelvis_pose_msg_sub_;
  //    ros::Subscriber pelvis_base_walking_msg_sub_;
  ros::Subscriber pelvis_reset_msg_sub_;

  tf::TransformBroadcaster broadcaster_;
  tf::StampedTransform pelvis_trans_;

  geometry_msgs::PoseStamped pelvis_pose_;
  geometry_msgs::PoseStamped pelvis_pose_old_;
  geometry_msgs::PoseStamped pelvis_pose_base_walking_;
  geometry_msgs::PoseStamped pelvis_pose_offset_;

  geometry_msgs::PoseStamped pelvis_pose_base_walking_new_;
  geometry_msgs::PoseStamped pelvis_pose_offset_new_;

  double transform_tolerance_;
  double err_tol_;

  bool is_moving_walking_;

  boost::mutex mutex_;

public:
  void initialize();
  void pelvisPoseCallback(const geometry_msgs::PoseStamped::ConstPtr &msg);
  //    void pelvisPoseBaseWalkingCallback(const
  //    geometry_msgs::PoseStamped::ConstPtr& msg);
  void pelvisPoseResetCallback(const std_msgs::String::ConstPtr &msg);
  Eigen::MatrixXd calcVWerr(Eigen::MatrixXd tar_position,
                            Eigen::MatrixXd curr_position,
                            Eigen::MatrixXd tar_orientation,
                            Eigen::MatrixXd curr_orientation);

  // constructor
  HUMANOID_ROBOTLocalization();
  // destructor
  ~HUMANOID_ROBOTLocalization();

  void update();
  void process();
};

} // namespace humanoid_robot_intelligence_control_system_op

#endif // THORMANG3_LOCALIZATION_H_
