include ../../config.mk

default: run

find_mnemo.o:
	cd ../../src/ ; \
		make find_mnemo.o
	mv ../../src/find_mnemo.o .

parse_line.o:
	cd ../../src/ ; \
		make parse_line.o
	mv ../../src/parse_line.o .

test: find_mnemo.o parse_line.o
	$(CC) $(CFLAGS) $(DBCFLAGS) find_mnemo.o parse_line.o test.c -o test

run: test
	./test < input.txt > out.txt
	./test < input_error.txt 2> out_error.txt
	vimdiff out.txt expected_output.txt
	vimdiff out_error.txt expected_output_error.txt

clean:
	rm test out.txt find_mnemo.o parse_line.o out_error.txt 
