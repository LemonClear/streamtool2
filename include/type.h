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
#ifndef __TYPE_H__
#define __TYPE_H__

/*address*/
typedef unsigned long address_t; //32bit or 64bit according to cpu

/*register*/
typedef unsigned long long reg64_t; //64bit
typedef unsigned int       reg32_t; //32bit

/*byte*/
typedef unsigned char byte_t; //8bit

/*fp16*/
typedef short int half; //16bit

/*x86 masks*/
#define BYTE_MASK  0x00000000000000FF; //8bit
#define WORD_MASK  0x000000000000FFFF; //16bit
#define DWORD_MASK 0x00000000FFFFFFFF; //32bit
#define QWORD_MASK 0xFFFFFFFFFFFFFFFF; //64bit

/*arm amba bus masks*/
#define ARM_AMBA_BYTE_MASK  0x00000000000000FF; //8bit
#define ARM_AMBA_HWORD_MASK 0x000000000000FFFF; //16bit
#define ARM_AMBA_WORD_MASK  0x00000000FFFFFFFF; //32bit
#define ARM_AMBA_DWORD_MASK 0xFFFFFFFFFFFFFFFF; //64bit

/**/


#endif
