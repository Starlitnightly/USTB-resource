CC = g++
CXX = g++
CPPFLAGS = -I../include -std=c++11 -Wall -Wextra -g 
LDFLAGS = -std=c++11 -lpng

EXENAME = test

.PHONY : clean TAGS

all : $(EXENAME)
	mv $(EXENAME) ../

tree.o : ../include/pxl.h ../include/suan_png.h /usr/include/libpng16/png.h

test.o : ../include/pxl.h ../include/suan_png.h ../include/tree.h /usr/include/libpng16/png.h


test : suan_png.o pxl.o tree.o

clean :
	-rm -rf *.o test *.dSYM

TAGS : clean all
