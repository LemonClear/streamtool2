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

# 3.Build source dir
ifeq ($(BUILD_SRC),)

# 4.Output to separate dir
ifeq ("$(origin O)", "command line")
  BUILD_OUTPUT := $(O)
endif

# 5.Cancel implicit rules on top Makefile
$(CURDIR)/Makefile Makefile: ;

ifneq ($(words $(subst :, ,$(CURDIR))), 1)
  $(error main directory cannot contain spaces nor colons)
endif

# 6.BUILD_OUTPUT dir exist(or use -O dir), Run increasement make
ifneq ($(BUILD_OUTPUT),)
saved-output := $(BUILD_OUTPUT)
BUILD_OUTPUT := $(shell mkdir -p $(BUILD_OUTPUT) && cd $(BUILD_OUTPUT) && pwd)
$(if $(BUILD_OUTPUT),, $(error failed to create output directory "$(saved-output)"))

PHONY += $(MAKECMDGOALS) sub-make

$(filter-out _all sub-make $(CURDIR)/Makefile, $(MAKECMDGOALS)) _all: sub-make
	@:

## invoke a increasement make in the output directory, passing relevant variables
sub-make:
	$(MAKE) -C $(BUILD_OUTPUT) BUILD_SRC=$(CURDIR) \
	-f $(CURDIR)/Makefile $(filter-out _all sub-make,$(MAKECMDGOALS))

## end increasement make, and avoid full build
skip-makefile := 1
endif # ifneq ($(BUILD_OUTPUT),)

endif # ifeq ($(BUILD_SRC),)

# 7.BUILD_OUTPUT dir not exist, Run full make
ifeq ($(skip-makefile),)

## 7.1 set source dir
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

## set version header
version_h := include/version.h

## simulator version 
SIMUVERSION = $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)
export VERSION PATCHLEVEL SUBLEVEL SIMUVERSION

## Make variables (CC, etc...)
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

export CONFIG_SHELL AS LD CC AR NM STRIP OBJCOPY OBJDUMP CFLAGS CXXFLAGS ARFLAG
export MAKE

## simulator main entry 
PHONY += simu
_all: simu

## 3rdparty controller libs
ARCHLIBS        := -L./arch/riscv/ -lRiscv -lpthread
SUBDIRS         := ./kernel ./lib
INCLUDE_DIRS    := -I./include -I./arch/include -I./lib/include -I./kernel/include
source          := $(wildcard *.c)
objects         := $(patsubst %.c,%.o,$(source))

## main compile
simu:$(objects) $(SUBDIRS)
	$(CC) $< -o $@ $(ARCHLIBS)

$(objects):%o:%c
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDE_DIRS)

$(SUBDIRS):trace
	+$(MAKE) -C $@

trace:
	@echo $(SUBDIRS)
	@echo 'bengin compile...'


PHONY += help
help:
	@echo  'Cleaning targets:'
	@echo  '  clean           - Remove most generated files but keep the .config'


endif # skip-makefile


PHONY += clean
clean:


# End-1.Force
PHONY += FORCE
FORCE:

# End.Declare the contents of the PHONY variable as phony
.PHONY: $(PHONY)
