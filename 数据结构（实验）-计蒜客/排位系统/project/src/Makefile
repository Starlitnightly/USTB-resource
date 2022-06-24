CC = g++
CXX = g++
CPPFLAGS = -I../include -std=c++11 -Wall -Wextra -g
LDFLAGS = -std=c++11

EXENAME = part1 test score_board

.PHONY : clean TAGS all

all : $(EXENAME)
	mv $(EXENAME) ../

part1 : part1.o heap.o

part1.o : ../include/heap.h

score_board.o : ../include/heap.h

score_board : heap.o

clean :
	-rm -rf *.o $(EXENAME) *.dSYM

TAGS : clean all
