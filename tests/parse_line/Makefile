include ../../config.mk

default: run

parse_line.o:
	cd ../../src/ ; \
		make parse_line.o
	mv ../../src/parse_line.o .

test: parse_line.o
	$(CC) $(CFLAGS) $(DBCFLAGS) parse_line.o test.c -o test

run: test
	./test < input.txt > out.txt
	./test < input_error.txt 2> out_error.txt
	vimdiff out.txt expected_output.txt
	vimdiff out_error.txt expected_output_error.txt

clean:
	rm test out.txt parse_line.o out_error.txt 
