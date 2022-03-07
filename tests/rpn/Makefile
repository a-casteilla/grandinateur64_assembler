include ../../config.mk

C := import_symbols.c scopes.c rpn.c conv_string.c sym.c pointer.c
H := common.h import_symbols.h scopes.h mnemonic.h rpn.h conv_string.h sym.h pointer.h
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
	./test < input.txt > out.txt
	vimdiff out.txt expected_output.txt
	gcov $C || echo "gcov is not installed on this computer"
	mkdir gcovr || rm -f gcovr/*
	python -m gcovr --output gcovr/gcovr.html --html-details \
		|| echo "gcovr is not installed on this computer"

clean:
	rm -rf test out.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/ 
