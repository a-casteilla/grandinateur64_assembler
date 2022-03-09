include ../../config.mk

C := conv_string.c
H := conv_string.h
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
	vimdiff out.txt expected_output.txt
	gcov $C || echo "gcov is not installed on this computer"
	mkdir gcovr || rm -f gcovr/*
	python -m gcovr --output gcovr/gcovr.html --html-details \
		|| echo "gcovr is not installed on this computer"

clean:
	rm -rf test out.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/
