include ../../config.mk

C := import_symbols.c scopes.c sym.c
H := common.h import_symbols.h scopes.h mnemonic.h sym.h
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
	./test input_1.sym input_2.sym > out_1.txt
	./test input_2.sym input_1.sym > out_2.txt
	./test input_1.sym input_zero.sym > out_3.txt
	./test input_zero.sym input_1.sym > out_4.txt
	vimdiff out_1.txt expected_output_1.txt
	vimdiff out_2.txt expected_output_2.txt
	vimdiff out_3.txt expected_output_3.txt
	vimdiff out_4.txt expected_output_4.txt
	gcov $C || echo "gcov is not installed on this computer"
	mkdir gcovr || rm -f gcovr/*
	python -m gcovr --output gcovr/gcovr.html --html-details \
		|| echo "gcovr is not installed on this computer"

clean:
	rm -rf test out*.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/ 
