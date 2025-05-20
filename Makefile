# Compiler and flags
CC := gcc
CFLAGS := -Iinclude -Ivendor/wren/src/include -lm

# Choose between RAWTERM or MAX7219
FEATURES := -DRAWTERM

# Directories
SRC_DIR := src
BUILD_DIR := build
WREN_DIR := vendor/wren
BIN := $(BUILD_DIR)/cloger

# Find all .c files recursively in src/
SRCS := $(shell find $(SRC_DIR) -name '*.c')
# Replace .c with .o and src/ with build/
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

WREN_SRCS := $(shell find $(WREN_DIR) -name '*.c')
WREN_OBJS := $(patsubst $(WREN_DIR)/%.c,$(BUILD_DIR)/%.o,$(WREN_SRCS))

# Default target
all: $(BIN)

# Link object files into binary
$(BIN): $(OBJS) $(WREN_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@

# Compile .c to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(FEATURES) -Wall -c $< -o $@

$(BUILD_DIR)/%.o: $(WREN_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(FEATURES) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

