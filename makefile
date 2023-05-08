INCLUDE = ./

# Compiler flags
CPPFLAGS = -std=c++20 -pedantic-errors -Wall -Wextra -g 
CC = g++


quickpop_test.out : quickpop_test.o 
    $(CC) $(CPPFLAGS) -I $(INCLUDE) $^ -o $@ -pthread

3sum.out : 3sum.o
    $(CC) $(CPPFLAGS) -I $(INCLUDE) $^ -o $@ 

countbits.out : countbits.o
    $(CC) $(CPPFLAGS) -I $(INCLUDE) $^ -o $@ 

lists.out : lists.o
    $(CC) $(CPPFLAGS) -I $(INCLUDE) $^ -o $@ 

mtxtest.out : mtxtest.o
    $(CC) $(CPPFLAGS) -I $(INCLUDE) $^ -o $@ -pthread

treetest.out : treetest.o
    $(CC) $(CPPFLAGS) -I $(INCLUDE) $^ -o $@ 

ood_test.out : ood_test.o ood.o
    $(CC) $(CPPFLAGS) -I $(INCLUDE) $^ -o $@

.PHONY: clean
clean : 
    rm -f .hex.out .so.o