INCLUDE = ./
SRC = ./
# Compiler flags
CPPFLAGS = -std=c++20 -pedantic-errors -Wall -Wextra -g 
CC = g++


quickpop_test.out : 
	$(CC) $(CPPFLAGS) -I $(INCLUDE) ./quickpop_test.cpp  -o $@ -pthread

.PHONY: clean
clean : 
	rm -f .hex.out .so.o