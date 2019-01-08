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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "common.h"


/**
 * poweron - power on the product
 * @product: pointer to the product
 *
 */
int poweron(ip *product)
{
        int ret = -1;
        printf("poweron!\n");

ret_on:
        return ret;
}


/**
 * poweroff - power off the product
 * @product: pointer to the product
 *
 */
int poweroff(ip *product)
{
        int ret = -1;
        printf("poweroff!\n");

ret_off:
        return ret;
}


/**
 * poweroff - power off the product
 * @product: pointer to the product
 *
 */
int poweridle(ip *product)
{
        int ret = -1;
        printf("power idle\n");

ret_idle:
        return ret;
}
