BIN := build/chatclient
INCLUDE_DIR := -I../spider/translayor/src -I../spider/logging/src
CXX_SRC_DIR := src
TARGET_DIR := build/targets
OBJ_DIR := build/objs

CC := gcc
CXX := g++
LD := g++

CFLAGS := $(INCLUDE_DIR) -Wall -O3 -fPIC
CXXFLAGS := -std=c++11

LDFLAGS := -L"../spider/translayor/build" -L"../spider/logging/build" -lspider -llogging -lpthread

include ../builder/Makefile.executable