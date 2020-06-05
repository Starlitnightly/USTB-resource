CC = g++
CXX = g++
CPPFLAGS = -I../include -std=c++11 -Wall -Wextra -g
LDFLAGS = -std=c++11

EXENAME = part1 part2 test word_check

.PHONY : clean

all : run

run : $(EXENAME)
	mv $(EXENAME) ../

word_check.o : ../include/hashtable.h ../include/dict.h

word_check : word_check.o hashtable.o dict.o

part1.o : ../include/hashtable.h

part1 : hashtable.o

clean :
	rm -rf *.o *.dSYM result.txt $(EXENAME)
