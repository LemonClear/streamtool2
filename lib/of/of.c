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
#include "common.h" /*FIXME: to be removed*/


/**
 * of_defconfig - parse xxxx_defconfig
 * @path:       defconfig file path
 * @params:     param struct
 *
 */
int of_defconfig(const char *path, param *params)
{
        int ret = -1;

        FILE *stream = NULL;
        char *line = NULL;
        size_t len = 0;
        ssize_t nread = 0;

        char *ptr = NULL;
        char ch = '=';

        /*begin*/
        if (unlikely(!params)) {
                ERROR("param struct is null !!!\n");
                goto ret_defconfig;
        }

        if (unlikely(!path)) {
                ERROR("path is null !!!\n");
                goto ret_defconfig;
        }

        if (unlikely(access(path, F_OK))) {
                ERROR("defconfig file {%s} not exist !!!\n", path);
                goto ret_defconfig;
        }

        /*open*/
        stream = fopen(path, "r");
        if (unlikely(!stream)) {
                ERROR("fopen file {%s} failed !!!\n", path);
                goto ret_config;
        }

ret_defconfig:
        return ret;
}
