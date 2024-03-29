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

#include "humanoid_robot_intelligence_control_system_tuning_module/tuning_data.h"

namespace humanoid_robot_intelligence_control_system_op {

TuningData::TuningData() {}

TuningData::~TuningData() {}

void TuningData::clearData() {
  joint_name_.clear();

  position_.clear();
  velocity_.clear();
  effort_.clear();

  p_gain_.clear();
  i_gain_.clear();
  d_gain_.clear();
}

} // namespace humanoid_robot_intelligence_control_system_op
