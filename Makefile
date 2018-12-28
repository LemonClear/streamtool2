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
objtree         := .
src             := $(srctree)
obj             := $(objtree)

export srctree objtree

## out dir
BUILD_OUTPUT  = $(srctree)/out
BUILD_OUTPUT := $(shell mkdir -p $(BUILD_OUTPUT) && cd $(BUILD_OUTPUT) && pwd)
$(if $(BUILD_OUTPUT),, $(error failed to create output directory "$(saved-output)"))

export BUILD_OUTPUT

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
CFLAGS          = -g
CXXFLAGS        = 
ARFLAG          = -rcs
AWK             = awk

export CONFIG_SHELL AS LD CC AR NM STRIP OBJCOPY OBJDUMP CFLAGS CXXFLAGS ARFLAG AWK
export MAKE

# 5.simulator main entry 
PHONY += simu
_all: simu

# 6.libs includes objects
CLIBS           := 
ARCHLIBS        := -L$(srctree)/arch/riscv/ -lRiscv -lpthread
SUBDIRS         := $(srctree)/kernel #$(srctree)/lib
INCLUDE_DIRS    := -I$(srctree)/include -I$(srctree)/arch/include -I$(srctree)/lib/include -I$(srctree)/kernel/include
#source          := $(wildcard *.c)
objects         := $(BUILD_OUTPUT)/*.o

export CLIBS ARCHLIBS INCLUDE_DIRS

# 7.main compile
simu:$(SUBDIRS)
	$(CC) $(objects) -o $@
	mv $@ $(BUILD_OUTPUT)

## build sub-dirs
$(SUBDIRS):trace
	+$(MAKE) -C $@

trace:
	@echo 'bengin compile...... $(SUBDIRS)'


PHONY += clean
clean:
	$(shell rm -rf $(BUILD_OUTPUT))


# End-1.Force
PHONY += FORCE
FORCE:

# End.Declare the contents of the PHONY variable as phony
.PHONY: $(PHONY)
