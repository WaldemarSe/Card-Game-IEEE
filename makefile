CC = gcc

SRC_DIR = src
LIB_DIR = src/libraries src/entities
OBJ_DIR = src/obj

SRCS = $(shell find $(SRC_DIR) -name "*.c")

OBJS = $(sort $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o))))

# COMPILER FLAGS
INC_DIRS = $(shell find $(LIB_DIR) -type d)
CFLAGS = -Wall -Wextra -std=c11 $(addprefix -I,$(INC_DIRS)) -IC:/raylib/raylib/src -I$(SRC_DIR)

# LINKER FLAGS
TARGET = cardGame.exe
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

vpath %.c $(SRC_DIR) $(INC_DIRS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean