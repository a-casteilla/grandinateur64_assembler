include ../../config.mk

C := import_symbols.c scopes.c sym.c pointer.c
H := common.h import_symbols.h scopes.h mnemonic.h sym.h pointer.h
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
	@./test input.sym > out.txt
	@./test input_zero.sym > out_zero.txt
	@vimdiff out.txt expected_output.txt
	@vimdiff out_zero.txt expected_output_zero.txt
	@gcov $C || echo "gcov is not installed on this computer" >&2
	@mkdir gcovr || rm -f gcovr/*
	@python -m gcovr --output gcovr/gcovr.html --html-details \
		|| echo "gcovr is not installed on this computer" >&2

clean:
	rm -rf test out*.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/
