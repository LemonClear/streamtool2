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
#include <unistd.h>
#include "compiler.h"
#include "logger.h"


/**
 * of - 
 * @:
 *
 */
void of()
{
        char* name = "of";

        DEBUG("My name = %s\n", name);
}


/**
 * parseline - parse a line of strings
 * @line:  pointer to a line of strings
 * @sep:   pointer to the delimit separator
 *
 */
int parseline(const char *line, char *sep)
{
        FILE *stream = NULL;
        int ret = -1;
        char *config = "./product.reg";

        if (unlikely(!line)) {
                WARNING("line is empty\n");
                goto ret_config;
        }

        /*begin*/
        if (unlikely(access(config, F_OK))) {
                WARNING("register config file %s is null !!! use default config !!!\n",
                                config);
                ret = 0;
                goto ret_config;
        }

        //FIXME: todo...
        //FIXME: getline(stream);

ret_config:
        return ret;
}
