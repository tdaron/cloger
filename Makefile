# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Iinclude

# Choose between RAWTERM or MAX7219
FEATURES := -DRAWTERM

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN := $(BUILD_DIR)/cloger

# Find all .c files recursively in src/
SRCS := $(shell find $(SRC_DIR) -name '*.c')
# Replace .c with .o and src/ with build/
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
all: $(BIN)

# Link object files into binary
$(BIN): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@

# Compile .c to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(FEATURES) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

