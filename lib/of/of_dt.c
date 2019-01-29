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
 * of_regconfig - parse regconfig.xxx
 * @path:      regconfig file path
 * @reglist:   pointer to regist
 * @delimit:   delimit charactor
 *
 * FIXME: to be replace by dt
 */
int of_regconfig(const char *path, regs **reglist, char delimit)
{
        int ret = -1;

        FILE *stream = NULL;
        char *line = NULL;
        size_t len = 0;
        ssize_t nread = 0;

        char *str = NULL;
        size_t strlen = 0;
        int id = 0;

        /*begin*/
        if (unlikely(!reglist)) {
                ERROR("product reglist is null !!!\n");
                goto ret_config;
        }

        if (unlikely(!path)) {
                ERROR("path is null !!!\n");
                goto ret_config;
        }

        if (unlikely(access(path, F_OK))) {
                /*regconfig file may absent*/
                WARNING("regconfig file {%s} not exist !!!\n", path);
                ret = 0;
                goto ret_config;
        }

        /*open*/
        stream = fopen(path, "r");
        if (unlikely(!stream)) {
                ERROR("fopen file {%s} failed !!!\n", path);
                goto ret_config;
        }

        /*parse each line*/
        while (-1 != (nread = getline(&line, &len, stream))) {
                /*bypass '#' lines*/
                if (unlikely('#' == *line)) continue;

                /*default delimit*/
                if (unlikely(!delimit))
                        delimit = '\t';
                if (unlikely(!strchr(line, delimit)))
                        delimit = ' ';
                if (unlikely(!strchr(line, delimit))) {
                        WARNING("wrong line format !!!\n");
                        continue;
                }

                /*1 -> name*/
                str = line;
                strlen = strchr(str, delimit) - str;
                strncpy(reglist[id]->name, str, strlen);

                /*2 -> address*/
                str = strchr(str, delimit) + 1;
                reglist[id]->address = (address32_t)strtol(str, NULL, 16);

                /*3 -> value*/
                str = strchr(str, delimit) + 1;
                reglist[id]->value = (reg32_t)strtol(str, NULL, 16);

                /*next element in reglist*/
                id++;
        }

        /*close*/
        ret = fclose(stream);
        if (unlikely(ret)) {
                WARNING("close file {%s} failed !!!\n", path);
                goto ret_config;
        }


ret_config:
        return ret;
}
