include ../../config.mk

C := parse_line.c find_mnemo.c compute_size.c \
     compute_addresses.c conv_string.c align.c scopes.c find_labels.c \
     sym.c pointer.c
H := parse_line.h find_mnemo.h compute_size.h compute_addresses.h conv_string.h \
     common.h mnemonic.h align.h scopes.h find_labels.h sym.h pointer.h
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
	@vimdiff out.txt expected_output.txt
	@gcov $C || echo "gcov is not installed on this computer" >&2
	@mkdir gcovr || rm -f gcovr/*
	@python -m gcovr --output gcovr/gcovr.html --html-details \
		|| echo "gcovr is not installed on this computer" >&2

clean:
	rm -rf test out.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/
