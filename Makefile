# VARIABLES

SRC_DIR = src
BUILD_DIR = build
INC_DIR = include
LIB_DIR = lib

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

CPP_FLAGS = $(SRC_FILES) -I $(INC_DIR)
OUTPUT_FLAG = -o $(BUILD_DIR)/main
LIBRARY_FLAGS = `pkg-config sdl3 --cflags --libs`
OPENGL_FLAGS = -lGL
GLAD_FLAGS = include/glad/src/glad.c -Iinclude/glad/include

default_target: default
.PHONY : default_target

# BUILD TARGETS

default:
	clang++ -std=c++20 $(CPP_FLAGS) $(OUTPUT_FLAG) $(LIBRARY_FLAGS) $(GLAD_FLAGS) $(OPENGL_FLAGS)
.PHONY : default

asan:
	clang++ -std=c++20 $(CPP_FLAGS) -o $(BUILD_DIR)/main_asan $(LIBRARY_FLAGS) $(GLAD_FLAGS) $(OPENGL_FLAGS) -fsanitize=address
.PHONY : asan

run:
	$(BUILD_DIR)/main

asan_run:
	$(BUILD_DIR)/main_asan

clean:
	rm build/*
