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

VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 1
EXTRAVERSION =

# 1.Default Target when none is given on the command line
PHONY := _all
_all:


# 2.Look for make include files relative to root of src 
MAKEFLAGS += -rR --include-dir=$(CURDIR)

# 3.set source dir
ifeq ($(BUILD_SRC),)
  srctree := .
else
  ifeq ($(BUILD_SRC)/,$(dir $(CURDIR)))
    srctree := ..
  else
    srctree := $(BUILD_SRC)
  endif
endif

export BUILD_SRC

## set objtree, src, obj
objtree           := .
src               := $(srctree)
obj               := $(objtree)
fullsrctree       := $(shell cd $(srctree) && pwd)

export srctree objtree

## out dir
BUILD_OUTPUT       = $(srctree)/out
BUILD_OUTPUT      := $(shell mkdir -p $(BUILD_OUTPUT) && cd $(BUILD_OUTPUT) && pwd)
$(if $(BUILD_OUTPUT),, $(error failed to create output directory "$(BUILD_OUTPUT)"))

BUILD_OUTPUT_LIBOBJS  = $(BUILD_OUTPUT)/libs
BUILD_OUTPUT_LIBOBJS := $(shell mkdir -p $(BUILD_OUTPUT_LIBOBJS) && cd $(BUILD_OUTPUT_LIBOBJS) && pwd)
$(if $(BUILD_OUTPUT_LIBOBJS),, $(error failed to create output directory "$(BUILD_OUTPUT_LIBOBJS)"))

export BUILD_OUTPUT BUILD_OUTPUT_LIBOBJS

# 4.Make variables (CC, etc...)
AS              = as
LD              = ld
CC              = gcc
CXX             = g++
AR              = ar
NM              = nm
STRIP           = strip
OBJCOPY         = objcopy
OBJDUMP         = objdump
CFLAGS          = -g -m64 -pipe -O2 -Wall -W -D_REENTRANT -fPIC
CXXFLAGS        = -m64 -pipe -frtti -std=c++11 -O2 -Wall -W -D_REENTRANT -fPIC
ARFLAG          = -r
AWK             = awk

export AS LD CC CXX AR NM STRIP OBJCOPY OBJDUMP CFLAGS CXXFLAGS ARFLAG AWK
export MAKE

# 5.simulator main entry 
PHONY += simu
_all: simu

# 6.libs includes objects
objects          := $(BUILD_OUTPUT)/*.o

ARCH_LIBS        :=

STATIC_LIBS_PATH := -L$(srctree)/out/

STATIC_LIBS      := -lof

DYNAMIC_LIBS_PATH:= -L$(srctree)/out/

DYNAMIC_LIBS     := -lc2xlayer \
		    -lcmath \
		    -ldebugger

SUBDIRS         := $(srctree)/kernel \
			$(srctree)/lib

INCLUDE_DIRS    := -I$(fullsrctree)/include/ \
		   -I$(fullsrctree)/arch/include/ \
		   -I$(fullsrctree)/lib/include/ \
		   -I$(fullsrctree)/kernel/include/

export ARCH_LIBS STATIC_LIBS_PATH STATIC_LIBS DYNAMIC_LIBS_PATH DYNAMIC_LIBS INCLUDE_DIRS

# 7.main compile
simu:$(SUBDIRS)
	$(CC) $(objects) -o $@ $(DYNAMIC_LIBS_PATH) $(DYNAMIC_LIBS) $(STATIC_LIBS_PATH) $(STATIC_LIBS)
	mv $@ $(BUILD_OUTPUT)

## build sub-dirs
$(SUBDIRS):trace
	+$(MAKE) -C $@

trace:
	@echo 'bengin compile...... $(SUBDIRS)'

## Dynamic Linkage SO Lib need install *.so to /lib/
install:
	sudo cp $(BUILD_OUTPUT)/*.so /lib/

unistall:
	sudo rm /lib/lib*.so


PHONY += clean
clean:
	rm -rf $(objects)
	rm -rf $(BUILD_OUTPUT)


# End-1.Force
PHONY += FORCE
FORCE:

# End.Declare the contents of the PHONY variable as phony
.PHONY: $(PHONY)
