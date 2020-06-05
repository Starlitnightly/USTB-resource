CC = g++
CXX = g++
CPPFLAGS = -I../include -std=c++11 -Wall -Wextra -g
LDFLAGS = -std=c++11

EXENAME = part1 part2 test simulator

.PHONY : clean TAGS all

all : $(EXENAME)
	mv $(EXENAME) ../

part1.o : part1.cpp ../include/stack.h ../include/queue.h

part2.o : part2.cpp ../include/stack.h ../include/queue.h

simulator.o : ../include/stack.h ../include/queue.h ../include/editor.cpp

clean :
	-rm -rf *.o $(EXENAME) *.dSYM

TAGS : clean all
