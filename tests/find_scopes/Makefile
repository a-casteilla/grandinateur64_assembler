include ../../config.mk

C := parse_line.c find_mnemo.c compute_size.c \
     compute_addresses.c conv_string.c align.c scopes.c
H := parse_line.h find_mnemo.h compute_size.h compute_addresses.h conv_string.h \
     common.h mnemonic.h align.h scopes.h
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

default: run

run: test
	@./test < input.txt > out.txt
	@./test < input_error_1.txt 2> out_error_1.txt > /dev/null
	@./test < input_error_2.txt 2> out_error_2.txt > /dev/null
	@./test < input_error_3.txt 2> out_error_3.txt > /dev/null
	@./test < input_big.txt > out_big.txt
	@vimdiff out.txt expected_output.txt
	@vimdiff out_error_1.txt expected_output_error_1.txt
	@vimdiff out_error_2.txt expected_output_error_2.txt
	@vimdiff out_error_3.txt expected_output_error_3.txt
	@vimdiff out_big.txt expected_output_big.txt
	@gcov $C || echo "gcov is not installed on this computer" >&2
	@mkdir gcovr || rm -f gcovr/*
	@python -m gcovr --output gcovr/gcovr.html --html-details \
		|| echo "gcovr is not installed on this computer" >&2

clean:
	rm -rf test out.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/ out_error_*.txt out_big.txt
