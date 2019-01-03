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
#include "common.h"
#include "c2xlayer.h"
#include "cmath.h"
#include "of.h"

int main(int argc, char* argv[])
{
        printf("hello word!!\n");
        c2xlayer_function();
        fp16_pt();
        of();
        of_dt();

        return 0;
}
