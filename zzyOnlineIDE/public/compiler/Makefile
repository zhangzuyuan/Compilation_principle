#########################################################
# FNAME		: Makefile                              #
# Version    	:                                       #
# FUNCTION	:                                       #
# CRATE		: 2017-07-10 changzehai                 #
# Copyright (C) 2017 changzehai. All Rights Reserved.   #
#########################################################
#源文件类型
# The valid suffixes are among of .c, .C, .cc, .cpp, .CPP, .c++, .cp, or .cxx.
# SRCEXTS   := .c      # C program
SRCEXTS   := .cpp    # C++ program
#SRCEXTS	    := .c

#source file
#源文件(下面是例子，自己参照修改)
HDRS		:= mfs_init.h

SRCS		:= mfs_shm_func.c \
                   mfs_file_func.c \
                   mfs_init.c


#目标文件名，输入任意你想要的执行文件名(下面是例子，自己参照修改)
OBJS		:= mfs_shm_func.o \
                   mfs_file_func.o \
                   mfs_init.o

PROGRAM		:= mfsInit

#指定用到的头文件和库文件路径指定(根据需要自行添加)
INCLUDE		:= -I. \
		   -I/include

#LIBS		:= -L/usr/lib \
		   -L/usr/lib64

#目标文件夹指定
HOST_LINUX	= ./linux

#编译器
#CC		= g++  #c++
CC      	= gcc  #c

#make工具, Makefile指定
MAKE		= make
MAKEFILE	= Makefile


#compile and lib parameter
#编译参数
LDFLAGS		:=
DEFINES		:=
CFLAGS		:= -g -Wall -O3 $(DEFINES) $(INCLUDE)
CXXFLAGS	:= $(CFLAGS) -DHAVE_CONFIG_H


#下面的基本上不需要做任何改动了
TARGET			= all clean
TARGET_LINUX	= $(TARGET:=_linux)

default		: all

$(OBJS)		:   $(HDRS) $(SRCS)
				@if [ ! -d $(HOST_LINUX) ]; then \
				echo "Make directory $(HOST_LINUX)"; mkdir -p $(HOST_LINUX); fi
				@echo "Compiling -c $(INCLUDE) $(@F:.o=$(SRCEXTS)) -o $@"
				@($(CC) $(CFLAGS) $(INCLUDE) -c $(@F:.o=$(SRCEXTS)) -o $@)

$(PROGRAM)	: $(OBJS)
				@if [ ! -d $(HOST_LINUX) ]; then \
				echo "Make directory $(HOST_LINUX)"; mkdir -p $(HOST_LINUX); fi
				@echo "Linking $(PROGRAM)"
				@($(CC) $(LDFLAGS) $(LIBS) $(OBJS) -o $@)
				@echo "done"


all_		: $(PROGRAM)

clean_		:
		@rm -f $(OBJS) $(PROGRAM)

$(TARGET)	:
			@(echo "Making on `uname -s` ... $(@F)"; \
			$(MAKE) -f $(MAKEFILE) $(@F:=_linux))

$(TARGET_LINUX):
			echo $(OBJS)
			@($(MAKE) -f $(MAKEFILE) \
			"OBJS=`for obj in $(OBJS); do echo -n $(HOST_LINUX)/$${obj} " "; done` " \
			"PROGRAM=$(HOST_LINUX)/$(PROGRAM)" \
			$(@F:linux=))