# VARIABLES

SRC_DIR = src
BUILD_DIR = build
INC_DIR = include
LIB_DIR = lib

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

CPP_FLAGS = $(SRC_FILES) -o $(BUILD_DIR)/main -I $(INC_DIR)/include -L $(LIB_DIR)
SDL3_FLAGS = `pkg-config sdl3 --cflags --libs`

default_target: default
.PHONY : default_target

# BUILD TARGETS

default:
	clang++ -std=c++20 $(CPP_FLAGS) $(SDL3_FLAGS)
.PHONY : default

run:
	$(BUILD_DIR)/main
