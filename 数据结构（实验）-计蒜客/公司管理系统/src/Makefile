CC = g++
CXX = g++
CPPFLAGS = -I../include -std=c++11 -Wall -Wextra -g
LDFLAGS = -std=c++11

EXENAME = part1 part2 test

.PHONY : clean TAGS all

all : $(EXENAME)
	mv $(EXENAME) ../

part1 : part1.o worker.o vector.o

part2 : part2.o workflow.o vector.o worker.o

part1.o : part1.cpp ../include/worker.h ../include/vector.h

part2.o : part2.cpp ../include/worker.h ../include/workflow.h ../include/vector.h

vector.o : ../include/worker.h

workflow.o : ../include/vector.h ../include/worker.h

clean :
	-rm -rf *.o $(EXENAME) *.dSYM

TAGS : clean all
