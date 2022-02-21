include ../../config.mk

C := parse_line.c find_mnemo.c conv_string.c def_statement.c
H := parse_line.h find_mnemo.h conv_string.h common.h mnemonic.h def_statement.h
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
	./test < input_void.txt > out_void.txt
	vimdiff out.txt expected_output.txt
	vimdiff out_void.txt expected_output_void.txt
	gcov $C || echo "gcov is not installed on this computer"
	mkdir gcovr || rm -f gcovr/*
	python -m gcovr --output gcovr/gcovr.html --html-details \
		|| echo "gcovr is not installed on this computer"

clean:
	rm -rf test out.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/ out_void.txt
