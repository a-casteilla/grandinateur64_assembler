include ../../config.mk

C := align.c
H := align.h
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
	gcov $C
	mkdir gcovr
	python -m gcovr --output gcovr/gcovr.html --html-details

clean:
	rm -rf test out.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/
