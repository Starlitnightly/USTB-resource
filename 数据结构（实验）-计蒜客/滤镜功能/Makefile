.PHONY: all clean
EXENAME = test

all: run

run:
	make -C src/ all

clean:
	make -C src/ clean
	-rm -rf $(EXENAME) *.dSYM pic/output.png
