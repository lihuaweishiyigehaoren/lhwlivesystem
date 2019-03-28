BIN := build/testlog
INCLUDE_DIR := -I../spider/logging/src
CXX_SRC_DIR := src
TARGET_DIR := build/targets
OBJ_DIR := build/objs

CC := gcc
CXX := g++
LD := g++

CFLAGS := $(INCLUDE_DIR) -Wall -O3 -fPIC
CXXFLAGS := -std=c++11
# LDFLAGS := 

LDFLAGS := -L"../spider/logging/build" -llogging -lpthread

include ../builder/Makefile.executable