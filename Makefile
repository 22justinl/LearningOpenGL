# VARIABLES

SRC_DIR = src
BUILD_DIR = build
INC_DIR = include
LIB_DIR = lib

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

CPP_FLAGS = $(SRC_FILES) -o $(BUILD_DIR)/main -I $(INC_DIR)
LIBRARY_FLAGS = `pkg-config sdl3 --cflags --libs`
OPENGL_FLAGS = -lGL
GLAD_FLAGS = include/glad/src/glad.c -Iinclude/glad/include

default_target: default
.PHONY : default_target

# BUILD TARGETS

default:
	clang++ -std=c++20 $(CPP_FLAGS) $(LIBRARY_FLAGS) $(GLAD_FLAGS) $(OPENGL_FLAGS)
.PHONY : default

run:
	$(BUILD_DIR)/main

clean:
	rm build/*
