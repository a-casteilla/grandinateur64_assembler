include ../../config.mk

C := parse_line.c find_mnemo.c compute_size.c conv_string.c
H := parse_line.h find_mnemo.h compute_size.h conv_string.h common.h mnemonic.h
O := $(C:%.c=%.o)

default: run

$H:
	cp ../../src/$@ .

$C:
	cp ../../src/$@ .

%.o: %.c $H
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $< -o $@

test: $O test.c
	$(CC) $(CFLAGS) $(DBCFLAGS) $^ -o $@

run: test
	./test < input.txt > out.txt
	./test < input_error.txt 2> out_error.txt > /dev/null
	vimdiff out.txt expected_output.txt
	vimdiff out_error.txt expected_output_error.txt
	gcov $C
	mkdir gcovr
	python -m gcovr --output gcovr/gcovr.html --html-details

clean:
	rm -rf test out.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/ out_error.txt
