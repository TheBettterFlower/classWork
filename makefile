CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17


all:
	$(CC) $(CFLAGS) src/*.cpp


