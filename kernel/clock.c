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
#include "of.h"


/**
 * clock_run - start clock
 * @product: pointer to product
 *
 */
int clock_run(ip *product)
{
        int ret = -1;

        /*begin*/
        if (unlikely(!product)) {
                printf("ERR: product absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_clockrun;
        }

        //FIXME: todo...
        /*run according to clock*/
        while (1) {
                tick_counter++;
        }

ret_clockrun:
        return ret;
}
