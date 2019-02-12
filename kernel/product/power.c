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
#include "logger.h"


/**
 * power_on - power on the product
 * @product: pointer to the product
 *
 */
int power_on(ip *product)
{
        int ret = -1;

        INFO("POWER ON\n");

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_power_on;
        }

        //FIXME: todo...
        //maybe something to be prepared before product power on

        /*call self poweron func*/
        ret = product->ops->poweron(product);
        if (unlikely(ret)) {
                ERROR("%s power on failed !!!\n", product->name);
                goto ret_power_on;
        }

        INFO("POWER ON DONE\n");

ret_power_on:
        return ret;
}


/**
 * power_off - power off the product
 * @product: pointer to the product
 *
 */
int power_off(ip *product)
{
        int ret = -1;

        INFO("POWER OFF\n");

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_power_off;
        }

        //FIXME: todo...

        INFO("POWER OFF DONE\n");

ret_power_off:
        return ret;
}


/**
 * power_idle - product enter idle
 * @product: pointer to the product
 *
 */
int power_idle(ip *product)
{
        int ret = -1;

        INFO("IDLE\n");

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_power_idle;
        }

        //FIXME: todo...

        INFO("IDLE DONE\n");

ret_power_idle:
        return ret;
}


/**
 * power_sleep - product enter sleep
 * @product: pointer to the product
 *
 */
int power_sleep(ip *product)
{
        int ret = -1;

        INFO("SLEEP\n");

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_power_sleep;
        }

        //FIXME: todo...

        INFO("SLEEP DONE\n");

ret_power_sleep:
        return ret;
}
