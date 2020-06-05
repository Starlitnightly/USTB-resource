.PHONY : all clean
EXENAME = part1 part2 test word_check

all : run

run :
	make -C src/ all
	./test

clean :
	make -C src/ clean
	-rm -rf $(EXENAME) *.dSYM output/part1.txt output/part2.txt
