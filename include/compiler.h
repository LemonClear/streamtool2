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
#ifndef __COMPILER_H__
#define __COMPILER_H__
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * This file defines all compiler related things, like gcc builtins
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/**
 * likely unlikely - gcc built in
 *
 */
# define likely(x)      __builtin_expect(!!(x), 1)
# define unlikely(x)    __builtin_expect(!!(x), 0)


/**
 * __same_type - return true if a and b have the same type
 *
 */
#ifndef __same_type
# define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))
#endif


/**
 * __compiletime_warning - print warning message while compile time
 *
 */
#ifndef __compiletime_warning
# define __compiletime_warning(message) __attribute__((__warning__(message)))
#endif


/**
 * __compiletime_error - print error while compile time
 *
 */
#ifndef __compiletime_error
# define __compiletime_error(message) __attribute__((__error__(message)))
#endif


/**
 * compiletime_assert - break build and emit msg if condition is false
 * @condition: a compile-time constant condition to check
 * @msg:       a message to emit if condition is false
 *
 */
#define __compiletime_assert(condition, msg, prefix, suffix)           \
        do {                                                            \
                extern void prefix ## suffix(void) __compiletime_error(msg); \
                if (!(condition))                                       \
                        prefix ## suffix();                             \
        } while (0)

#define _compiletime_assert(condition, msg, prefix, suffix) \
        __compiletime_assert(condition, msg, prefix, suffix)

#define compiletime_assert(condition, msg) \
        _compiletime_assert(condition, msg, __compiletime_assert_, __LINE__)


/**
 * BUILD_BUG_ON_MSG - break compile if a condition is true & emit supplied error
 *                    message.
 * @condition: the condition which the compiler should know is false.
 *
 */
#define BUILD_BUG_ON_MSG(cond, msg) compiletime_assert(!(cond), msg)


/**
 * offsetof - compute memer ofset of a struct
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#undef offsetof
#ifdef __compiler_offsetof
# define offsetof(TYPE, MEMBER)  __compiler_offsetof(TYPE, MEMBER)
#else
# define offsetof(TYPE, MEMBER)  ((size_t)&((TYPE *)0)->MEMBER)
#endif



#endif
