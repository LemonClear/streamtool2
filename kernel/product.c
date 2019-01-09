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
 * global variants
 * @global_state:   the whole product run state-machine
 *
 */
enum state global_state = OFF;


/**
 * product_init - init product
 * @product:    pointer to the product
 * @params:     init parameters
 *
 */
int product_init(ip *product, param *params)
{
        int ret = -1;
        printf("product init\n");
        //FIXME: todo...

ret_init:
        return ret;
}


/**
 * product_run - run this product
 * @product:    pointer to the product
 *
 */
int product_run(ip *product)
{
        int ret = -1;

        /*power on*/
        ret = poweron(product);
        if (unlikely(-1 == ret)) {
                printf("ERR: power on failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_run;
        }

        /*state machine change state*/
        global_state = RUN;

running:
        /*run*/
        while (RUN == global_state) {
                ret = powerrun(product);
                if (unlikely(-1 == ret)) {
                        printf("ERR: power run failed! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                        goto ret_run;
                }
        }

        /*idle*/
        while (IDLE == global_state) {
                //no clock, need clock wakeup
                ret = poweridle(product);
                if (unlikely(-1 == ret)) {
                        printf("ERR: power idle failed! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                        goto ret_run;
                }

                if (unlikely(RUN == global_state))
                        goto running;
        }

        /*sleep*/
        while (SLEEP == global_state) {
                //no power no clock, need outside clock wakeup
                ret = powersleep(product);
                if (unlikely(-1 == ret)) {
                        printf("ERR: power sleep failed! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                        goto ret_run;
                }

                if (unlikely(RUN == global_state))
                        goto running;
        }

        /*done*/
        ret = 0;

        /*power off*/
        poweroff(product);

ret_run:
        return ret;
}
