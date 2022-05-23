include ../../config.mk

C := pointer.c
H := pointer.h
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
	./test
	gcov $C || echo "gcov is not installed on this computer" >&2
	mkdir gcovr
	python -m gcovr --output gcovr/gcovr.html --html-details \
		|| echo "gcovr is not installed on this computer" >&2


clean:
	rm -rf test out.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/
