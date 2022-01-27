include ../../config.mk

default: run

align.o:
	cd ../../src ; \
	make align.o
	mv ../../src/align.o .

align.h:
	cp ../../src/align.h .

test: align.o align.h
	$(CC) $(CFLAGS) $(DBCFLAGS) align.o test.c -o test

run: test
	./test < input.txt > out.txt
	vimdiff out.txt expected_output.txt

clean:
	rm test out.txt
