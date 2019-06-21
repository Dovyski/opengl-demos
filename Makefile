###################################################################
# Makefile to setup and compile all projets on Linux.
# Type 'make help' in the command prompt to to see how to use this
# makefile and its rules.
#
# Author: Fernando Bevilacqua <fernando.bevilacqua@uffs.edu.br>
# License: MIT
###################################################################

CC = g++
LIBS = -lglfw -lGL -lm -lX11 -lglut -lGLU -ldl
CFLAGS = -g -Wall -Wno-deprecated

CURRENT_DIR := $(strip $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))

SRC_FOLDER := $(CURRENT_DIR)/src
DEMOS := $(shell ls $(SRC_FOLDER))
BUILD_FOLDER = $(CURRENT_DIR)/build/x64/Release
DATA_FOLDER = $(CURRENT_DIR)/data
BUILD_OBJ_FOLDER = $(CURRENT_DIR)/build/obj

clean:
	-rm -f $(BUILD_OBJ_FOLDER)/*.o
	-rm -f $(BUILD_FOLDER)/*

install-deps:
	sudo apt install build-essential cmake xorg-dev libglu1-mesa-dev libglfw3 libglfw3-dev freeglut3 freeglut3-dev libglew-dev mesa-utils mesa-common-dev

%::
	$(eval DEMO_NAME = $(MAKECMDGOALS))
	$(eval DEMO_SRC_DIR = $(SRC_FOLDER)/$(DEMO_NAME))
	$(eval DEMO_BIN_PATH = $(BUILD_FOLDER)/$(DEMO_NAME))

	@if [ -d "${DEMO_SRC_DIR}" ]; then \
		echo "Building demo: ${DEMO_NAME}"; \
		mkdir -p $(BUILD_OBJ_FOLDER); \
		mkdir -p $(BUILD_FOLDER); \
		cd $(BUILD_FOLDER); \
		$(CC) $(CFLAGS) $(DEMO_SRC_DIR)/*.c* -o $(DEMO_BIN_PATH) $(LIBS); \
		printf "Copying data files..."; \
		cp -R $(DATA_FOLDER)/* $(BUILD_FOLDER); \
		echo "done!"; \
		echo "Success! Run \"${DEMO_BIN_PATH}\" to start the demo."; \
	else  \
		echo "Invalid demo: \"${DEMO_NAME}\". Run \"make help\" for help."; \
	fi

all:
	@for DEMO in $(DEMOS); do \
		$(MAKE) $$DEMO; \
	done

help:
	@echo "Help info"
