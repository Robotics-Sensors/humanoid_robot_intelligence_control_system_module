/*******************************************************************************
 * Copyright 2017 ROBOTIS CO., LTD.
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

/* Author: Kayman */

#ifndef HUMANOID_ROBOT_OPEN_CR_MODULE_H_
#define HUMANOID_ROBOT_OPEN_CR_MODULE_H_

#include <boost/thread.hpp>
#include <eigen3/Eigen/Eigen>
#include <ros/callback_queue.h>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/String.h>

#include "humanoid_robot_intelligence_control_system_controller_msgs/StatusMsg.h"
#include "humanoid_robot_intelligence_control_system_controller_msgs/SyncWriteItem.h"
#include "humanoid_robot_intelligence_control_system_framework_common/sensor_module.h"
#include "humanoid_robot_intelligence_control_system_math/humanoid_robot_intelligence_control_system_linear_algebra.h"
#include "humanoid_robot_intelligence_control_system_math/humanoid_robot_intelligence_control_system_math_base.h"

namespace humanoid_robot_intelligence_control_system_op {

class OpenCRModule
    : public humanoid_robot_intelligence_control_system_framework::SensorModule,
      public humanoid_robot_intelligence_control_system_framework::Singleton<
          OpenCRModule> {
public:
  OpenCRModule();
  virtual ~OpenCRModule();

  /* ROS Topic Callback Functions */
  void initialize(
      const int control_cycle_msec,
      humanoid_robot_intelligence_control_system_framework::Robot *robot);
  void process(
      std::map<
          std::string,
          humanoid_robot_intelligence_control_system_framework::Dynamixel *>
          dxls,
      std::map<std::string,
               humanoid_robot_intelligence_control_system_framework::Sensor *>
          sensors);

private:
  const double G_ACC = 9.80665;
  const double GYRO_FACTOR = 2000.0 / 32800.0;
  const double ACCEL_FACTOR = 2.0 / 32768.0;
  const bool DEBUG_PRINT;

  void queueThread();

  double getGyroValue(int raw_value);
  double getAccValue(int raw_value);
  void publishIMU();

  void handleButton(const std::string &button_name);
  void publishButtonMsg(const std::string &button_name);
  void handleVoltage(double present_volt);
  void publishStatusMsg(unsigned int type, std::string msg);
  void publishDXLPowerMsg(unsigned int value);
  double lowPassFilter(double alpha, double x_new, double &x_old);

  int control_cycle_msec_;
  boost::thread queue_thread_;
  std::map<std::string, bool> buttons_;
  std::map<std::string, ros::Time> buttons_press_time_;
  ros::Time button_press_time_;
  ros::Time last_msg_time_;
  std::map<std::string, double> previous_result_;
  double previous_volt_;
  double present_volt_;

  sensor_msgs::Imu imu_msg_;

  /* subscriber & publisher */
  ros::Publisher imu_pub_;
  ros::Publisher button_pub_;
  ros::Publisher status_msg_pub_;
  ros::Publisher dxl_power_msg_pub_;
};

} // namespace humanoid_robot_intelligence_control_system_op

#endif /* HUMANOID_ROBOT_OPEN_CR_MODULE_H_ */
