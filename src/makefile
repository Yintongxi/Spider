.PHONY:spider 

#version 2.0 make less time 
#TARGET=app#用于存储变量名
#CC=gcc #用于存储编译器版本
#INCLUDE_PATH=../include#用于存储头文件路径
#LIBRARY_PATH=../lib#用于存储库的路径
#CFLAGS=-c -I$(INCLUDE_PATH)#用于存储编译选项 
				 
#SOURCEFILE=$(wildcard *.c)
#DFILE=$(patsubst %.c,%.o,$(SOURCEFILE)) 
		  
#$(TARGET):$(DFILE)
#$(CC) $^ -o $@
									    
#%.O:%.C
#$(CC) $(CFLAGS) $<
														 
INCLUDE_PATH=../include
CC=gcc
CFLAGS=-I$(INCLUDE_PATH) -Wall -c -g
#根目录下的Makefile用命令：make -C./src #跳转到src中执行里面的makefile
CPPFLAGS=
LDFLAGS=-lssl -lcrypto
LIBRARY_PATH=../library
TARGET=BAIKE_SPIDER
RM=sudo rm -rf
CP=sudo cp
SFILE=$(wildcard *.c)
DFILE=$(patsubst %.c,%.o,$(SFILE));
																		 
$(TARGET):$(DFILE) #编译主目标
	$(CC) $^ $(LDFLAGS) -o $@
																									
%.o:%.c #次级目标
	$(CC) $(CFLAGS) $<
	
clean:
	$(RM) $(DFILE) Result.html


distclean:

 #卸载程序和删除配置文件

 

install:

#拷贝安装到指定位置
