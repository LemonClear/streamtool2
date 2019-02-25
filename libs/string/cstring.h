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
#ifndef __CSTRING_H__
#define __CSTRING_H__
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * This file defines all cstring functions
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "cerr.h"


/*cstring functions*/
char *hexdi2s(int num);
char *hexdui2s(unsigned int num);
char *hexdl2s(long num);
char *hexdul2s(unsigned long num);
char *hexdll2s(long long num);
char *hexdull2s(unsigned long long num);


#endif
