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
	gcov $C
	mkdir gcovr
	python -m gcovr --output gcovr/gcovr.html --html-details

clean:
	rm -rf test out.txt $C $H *.o *.gcda *.gcno *.gcov gcovr/
