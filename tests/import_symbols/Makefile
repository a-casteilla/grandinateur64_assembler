default: run

assembler:
	cd ../.. ;\
	mv config.h config.h.bak ;\
	sed "s/\/\/#define unit_test_of_import_symbols/#define \
	unit_test_of_import_symbols/" < config.h.bak > config.h ;\
	make clean ; \
	make ; \
	mv assembler tests/import_symbols/ ; \
	make clean ; \
	mv config.h.bak config.h

run: assembler
	./assembler > out.txt
	vimdiff out.txt expected_output.txt

clean:
	rm assembler out.txt
