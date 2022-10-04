CC = gcc
CXX = g++
LD = g++
AR = ar

LFLAGS = 

ifdef DEBUG
CFLAGS = -g -O0
else
CFLAGS = -fPIC -O2 -fpermissive
endif
