CC = gcc

# 1. FIND ALL SOURCES
DIR ?= src
SRC_DIR = $(DIR)/src
LIB_DIR = Bibliotecas
OBJ_DIR = Bibliotecas/obj

# Find all .c files in project src AND all Bibliotecas subfolders
SRCS = $(shell find $(SRC_DIR) -name "*.c") \ $(shell find $(LIB_DIR) -name "*.c")

# 2. DEFINE OBJECTS
# We will put all objects in a flat 'obj' folder to avoid path issues
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

# 3. COMPILER FLAGS
# Find all directories for includes
INC_DIRS = $(shell find $(LIB_DIR) -type d)
CFLAGS = -Wall -Wextra -std=c11 $(addprefix -I,$(INC_DIRS)) -IC:/raylib/raylib/src -I$(SRC_DIR)

# 4. LINKER FLAGS
TARGET = $(DIR)/$(DIR).exe
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

all: $(TARGET)

# Link all objects together
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

# Rule for project source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for Bibliotecas source files (handles nested files)
# This vpath allows us to find .c files in any subfolder found earlier
vpath %.c $(SRC_DIR) $(INC_DIRS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean