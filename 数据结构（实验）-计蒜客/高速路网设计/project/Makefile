.PHONY: all clean
EXENAME = part1 part2 test

all: run

run:
	make -C src/ all

clean:
	make -C src/ clean
	-rm -rf $(EXENAME) *.dSYM
