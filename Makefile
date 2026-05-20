CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Isrc/time -Isrc/partida -Isrc/utils
TARGET = build/programa
SRC = src/main.c \
	src/time/time.c \
	src/time/bd_time.c \
	src/partida/partida.c \
	src/partida/bd_partida.c \
	src/utils/menu.c

.PHONY: all run clean

all: $(TARGET)

run: $(TARGET)
	./$(TARGET) $(PARTIDAS)

$(TARGET): $(SRC)
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf build
