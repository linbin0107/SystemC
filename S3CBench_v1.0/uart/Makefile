#===========================================================================
#
# File Name    : Makefile
# Description  : Makefile for FIR filter
# Release Date : 14/02/13
# Author       : PolYU
#
# Note         : Edit SYSTEMC_HOME path
# Revision History
#---------------------------------------------------------------------------
# Date      Version    Author      Description
#---------------------------------------------------------------------------
#14/12/13        1.0    PolyU       Makefile for FIR Filter
#============================================================================

TARGET	= uart.exe

SRCS	=  \
	main.cpp \
	tb_uart.cpp \
	uart.cpp

HDRS	=  \
	tb_uart.h \
	define.h \
	uart.h

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
swm1: CFLAGS += -DSWM1
swm2: CFLAGS += -DSWM2
swm1_tri: CFLAGS += -DSWM1_TRI
swm2_tri: CFLAGS += -DSWM2_TRI

$(TARGET) : $(OBJS)
	$(LINKER) -o "$@" $(LDFLAGS) $(OBJS) $(LIBS)

debug: $(OBJS)
	$(LINKER) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) $(DEBUG)

wave:  $(OBJS) 
	$(LINKER) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) $(WAVEFLAG)

swm1:  $(OBJS) 
	$(LINKER) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) $(SWM1FLAG)

swm2:  $(OBJS) 
	$(LINKER) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) $(SWM2FLAG)

swm1_tri:  $(OBJS) 
	$(LINKER) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) $(SWM1_TRIFLAG)

swm2_tri:  $(OBJS) 
	$(LINKER) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) $(SWM2_TRIFLAG)

main.o: main.cpp
	$(CC) $(CFLAGS) $(CWB_SC_INCL) $(INCL) -c $< -o $@
tb_uart.o: tb_uart.cpp 
	$(CC) $(CFLAGS) $(CWB_SC_INCL) $(INCL) -c $< -o $@  
uart.o: uart.cpp
	$(CC) $(CFLAGS) $(CWB_SC_INCL) $(INCL) -c $< -o $@ -fprofile-arcs -ftest-coverage

clean :
	@$(RM) -f $(OBJS) $(TARGET)

depend :
	makedepend -- $(INCL) $(CFLAGS) -- -Y -fMakefile.GNU $(SRCS)

