include ../../config.mk

C := parse_line.c find_mnemo.c compute_size.c compute_addresses.c conv_string.c align.c
H := parse_line.h find_mnemo.h compute_size.h compute_addresses.h conv_string.h \
     common.h mnemonic.h align.h
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
	@./test < input.txt > out.txt
	@./test < input_error_1.txt 2> out_error_1.txt > /dev/null
	@./test < input_error_2.txt 2> out_error_2.txt > /dev/null
	@./test < input_error_3.txt 2> out_error_3.txt > /dev/null
	@vimdiff out.txt expected_output.txt
	@vimdiff out_error_1.txt expected_output_error_1.txt
	@vimdiff out_error_2.txt expected_output_error_2.txt
	@vimdiff out_error_3.txt expected_output_error_3.txt
	@gcov $C || echo "gcov is not installed on this computer" >&2
	@mkdir gcovr || rm -f gcovr/*
	@python -m gcovr --output gcovr/gcovr.html --html-details \
		|| echo "gcovr is not installed on this computer" >&2

clean:
	rm -rf test out.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/ out_error_*.txt
