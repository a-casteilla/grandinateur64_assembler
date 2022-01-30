include ../../config.mk

default: run

conv_string.o:
	cd ../../src/ ; \
		make conv_string.o
	cp ../../src/conv_string.o .

test: conv_string.o
	$(CC) $(CFLAGS) $(DBCFLAGS) conv_string.o test.c -o test

run: test
	./test < input.txt > out.txt
	vimdiff out.txt expected_output.txt

clean:
	rm test out.txt conv_string.o
