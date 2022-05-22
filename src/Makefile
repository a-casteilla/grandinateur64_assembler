include ../config.mk

align.o: align.c 
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $^ -o $@

check_overlapping_areas.o: check_overlapping_areas.c 
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $^ -o $@

compute_addresses.o: compute_addresses.c 
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $^ -o $@

compute_size.o: compute_size.c 
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $^ -o $@

conv_string.o: conv_string.c 
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $^ -o $@

def_statement.o: def_statement.c 
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $^ -o $@

find_labels.o: find_labels.c 
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $^ -o $@

find_mnemo.o: find_mnemo.c 
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $^ -o $@

import_symbols.o: import_symbols.c 
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $^ -o $@

parse_line.o: parse_line.c 
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $^ -o $@

scopes.o: scopes.c 
	$(CC) $(CFLAGS) $(DBCFLAGS) -c $^ -o $@

documentation:
	doxygen .doc.setup

clean:
	rm -f align.o \
		check_overlapping_areas.o \
		compute_addresses.o \
		compute_size.o \
		conv_string.o \
		def_statement.o \
		find_labels.o \
		find_mnemo.o \
		import_symbols.o \
		parse_line.o \
		scopes.o
	rm -rf html latex
