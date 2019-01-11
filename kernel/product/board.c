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
 * board_init - init board with params
 * @product:   pointer to the product
 * @id:        device id
 * @params:    init parameters
 *
 * FIXME: most inits move to self->ops->init according to dt, except ops
 */
int board_init(ip *product, int id, param *params)
{
        int ret = -1;

        /*begin*/
        if (unlikely(!product) || unlikely(!params)) {
                printf("ERR: product or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

ret_init:
        return ret;
}
