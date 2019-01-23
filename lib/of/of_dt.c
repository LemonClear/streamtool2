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
#include "logger.h"


void of_dt()
{
        char* name = "of_dt";

        DEBUG("My name = %s\n", name);
}


/**
 * parse_regconfig - parse reg config file xxx.reg
 * @reglist:   pointer to reglist
 *
 * FIXME: to be replace by dt
 */
#if 0
int parse_regconfig(regs **reglist)
{
        int ret = -1;
        char *config = "./product.reg";

        if (unlikely(!reglist)) {
                ERROR("product reglist is null !!!\n");
                goto ret_config;
        }

        /*begin*/
        if (unlikely(access(config, F_OK))) {
                WARNNING("register config file %s is null !!! use default config !!!\n",
                                config);
                ret = 0;
                goto ret_config;
        }

        //FIXME: todo...

ret_config:
        return ret;
}
#endif
