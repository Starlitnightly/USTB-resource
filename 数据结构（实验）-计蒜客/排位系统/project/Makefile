.PHONY: all clean
EXENAME = part1 test score_board

all: run

run:
	make -C src/ all
	./test

clean:
	make -C src/ clean
	-rm -rf $(EXENAME) *.dSYM output/part1.txt output/part2.txt
