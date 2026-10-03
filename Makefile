CC = gcc
CFLAGS = -Wall -Wextra -O3 -Iinclude
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

SRCS = $(SRC_DIR)/diff_engine.c $(SRC_DIR)/lorenz_sim.c
OBJS = $(BUILD_DIR)/diff_engine.o $(BUILD_DIR)/lorenz_sim.o
TARGET = lorenz_sim

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

clean:
	rm -rf $(BUILD_DIR) $(TARGET) lorenz_output.csv

.PHONY: all clean