#==========================================================================
#
# File Name    : Makefile
# Description  : Makefile for disparity estimation
# Release Date : 16/06/13
# Author       : PolyU DARC Lab
#
# Note         : Edit SYSTEMC_HOME path
# Revision History
#---------------------------------------------------------------------------
# Date      Version  Author    Description
#---------------------------------------------------------------------------
# 16/17/13     1.0   PolyU     Makefile for dispariy estimator
#==========================================================================

TARGET	= disparity.exe

SRCS	=  \
	main.cpp \
	tb_disparity.cpp \
	disparity.cpp \
	pre_process.cpp 

HDRS	=  \
	disparity_top.h \
	disparity.h \
	define.h \
	pre_process.h \
	tb_disparity.h


ifneq (, $(wildcard /bin/uname))
CPU_ARCH = $(shell /bin/uname -m)
endif

ifeq ($(CPU_ARCH),x86_64)
CWB_LIB   = $(CYBER_PATH)/lib64
ARCH_FLAG = 
else
CWB_LIB   = $(CYBER_PATH)/lib
ARCH_FLAG = -m32
endif

ifdef CYBER_SYSTEMC_TARGET_ARCH
CWB_SC_ARCH = $(CYBER_SYSTEMC_TARGET_ARCH)
else
ifeq (, $(findstring Windows,$(OS)))
ifeq ($(CPU_ARCH),x86_64)
CWB_SC_ARCH = linux64
else
CWB_SC_ARCH = linux
endif
else
CWB_SC_ARCH = mingw
endif
endif

ifdef CYBER_SYSTEMC_HOME
CWB_SC_HOME = $(CYBER_SYSTEMC_HOME)
else
CWB_SC_HOME = $(CYBER_PATH)/osci
endif

CWB_SC_INCL = -I"$(CWB_SC_HOME)/include"
CWB_SC_LIB  = "$(CWB_SC_HOME)/lib-$(CWB_SC_ARCH)/libsystemc.a"

EMPTY	=
SPACE	= $(EMPTY) $(EMPTY)
ifeq (, $(wildcard  $(subst $(SPACE),\$(SPACE),$(CYBER_PATH))/gcc/bin))
CC	= g++
RM	= rm
else
CC	= "$(CYBER_PATH)/gcc/bin/g++"
RM	= "$(CYBER_PATH)/gcc/bin/rm"
endif
COVER   = -fprofile-arcs -ftest-coverage 
LINKER	= $(CC)
INCL	= -I"."
CFLAGS	= $(ARCH_FLAG) -O1
LDFLAGS	= $(ARCH_FLAG)
LIBS	= -lm $(CWB_SC_LIB)  -Wl,-rpath="$(CWB_LIB)" $(COVER)
OBJS	= $(notdir $(addsuffix .o,$(basename $(SRCS))))
debug: CFLAGS += -g -DDEBUG
wave: CFLAGS += -DWAVE_DUMP
cwom1: CFLAGS += -DCWOM1
cwom2: CFLAGS += -DCWOM2
cwm: CFLAGS += -DCWM

$(TARGET) : $(OBJS)
	$(LINKER) -o "$@" $(LDFLAGS) $(OBJS) $(LIBS)

debug: $(OBJS)
	$(LINKER) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) $(DEBUG)

wave:  $(OBJS) 
	$(LINKER) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) $(WAVEFLAG)

cwom1:  $(OBJS) 
	$(LINKER) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) $(CWOM1FLAG)

cwom2:  $(OBJS) 
	$(LINKER) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) $(CWOM2FLAG)

cwm:  $(OBJS) 
	$(LINKER) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) $(CWMFLAG)

main.o: main.cpp
	$(CC) $(CFLAGS) $(CWB_SC_INCL) $(INCL) -c $< -o $@
tb_disparity.o: tb_disparity.cpp
	$(CC) $(CFLAGS) $(CWB_SC_INCL) $(INCL) -c $< -o $@
disparity.o: disparity.cpp
	$(CC) $(CFLAGS) $(CWB_SC_INCL) $(INCL) -c $< -o $@ -fprofile-arcs -ftest-coverage
pre_process.o: pre_process.cpp
	$(CC) $(CFLAGS) $(CWB_SC_INCL) $(INCL) -c $< -o $@

clean :
	@$(RM) -f $(OBJS) $(TARGET)

depend :
	makedepend -- $(INCL) $(CFLAGS) -- -Y -fMakefile.GNU $(SRCS)
