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
#ifndef __LOGGER_H__
#define __LOGGER_H__
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * This file defines all log prints things
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "compiler.h"


/*log colors*/
#define LOG_FG_BLACK                "\033[30m"
#define LOG_FG_RED                  "\033[31m"
#define LOG_FG_GREEN                "\033[32m"
#define LOG_FG_YELLOW               "\033[33m"
#define LOG_FG_BLUE                 "\033[34m"
#define LOG_FG_VIOLET               "\033[35m"
#define LOG_FG_VIRDIAN              "\033[36m"
#define LOG_FG_WHITE                "\033[37m"
#define LOG_BG_BLACK                "\033[40m"
#define LOG_BG_RED                  "\033[41m"
#define LOG_BG_GREEN                "\033[42m"
#define LOG_BG_YELLOW               "\033[43m"
#define LOG_BG_BLUE                 "\033[44m"
#define LOG_BG_VIOLET               "\033[45m"
#define LOG_BG_VIRDIAN              "\033[46m"
#define LOG_BG_WHITE                "\033[47m"
#define LOG_END                     "\033[0m"


/*log level*/
#define LOG_LEVEL_ERROR             1
#define LOG_LEVEL_WARN              2
#define DBG_LEVEL_INFO              3
#define DBG_LEVEL_DEBUG             4


/*func definitions*/
#define ERROR \
        (printf("%sERROR:%s %s[%s, %s(), line%d, time%s]%s ", \
                LOG_FG_RED, LOG_END, LOG_BG_BLACK, \
                __FILE__, __func__, __LINE__, __TIME__, LOG_END), \
                printf)

#define WARNNING \
        (printf("%sWARNNING:%s %s[%s, %s(), line%d, time%s]%s ", \
                LOG_FG_YELLOW, LOG_END, LOG_BG_BLACK, \
                __FILE__, __func__, __LINE__, __TIME__, LOG_END), \
                printf)

#define INFO \
        (printf("%sINFO:%s %s[%s, %s(), line%d, time%s]%s ", \
                LOG_FG_GREEN, LOG_END, LOG_BG_BLACK, \
                __FILE__, __func__, __LINE__, __TIME__, LOG_END), \
                printf)

#define DEBUG \
        (printf("%sDEBUG:%s %s[%s, %s(), line%d, time%s]%s ", \
                LOG_FG_BLUE, LOG_END, LOG_BG_BLACK, \
                __FILE__, __func__, __LINE__, __TIME__, LOG_END), \
                printf)



#endif
