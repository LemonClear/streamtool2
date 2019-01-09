/*
#
# Copyright LemonClear
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
*/
#ifndef __CONFIG_H__
#define __CONFIG_H__
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * This file defines simulator configurations.
 * FIXME: will replaced by kconfig and dt
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/*core inside*/
#define CTLP_REG_COUNT  200
#define NCOP_REG_COUNT  200
#define TCOP_REG_COUNT  200
#define RAM_REG_COUNT   200
#define SUB_IP_COUNT    6

/*chip inside*/
#define CHIP_REG_COUNT  100
#define NOC_REG_COUNT   100
#define CHIP_REG_COUNT  100
#define SUB_CORE_COUNT  1024

/*board inside*/
#define BOARD_REG_COUNT 100
#define SUB_CHIP_COUNT  2

/*product inside*/
#define SUB_BOARD_COUNT 2




#endif
