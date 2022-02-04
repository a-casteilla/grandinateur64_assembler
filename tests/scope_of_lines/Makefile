default: run

assembler:
	cd ../.. ;\
	mv config.h config.h.bak ;\
	sed "s/\/\/#define unit_test_of_scope_of_lines/#define \
	unit_test_of_scope_of_lines/" < config.h.bak > config.h ;\
	make clean ; \
	make ; \
	mv assembler tests/scope_of_lines/ ; \
	make clean ; \
	mv config.h.bak config.h

run: assembler
	./assembler < input.txt > out.txt
	vimdiff out.txt expected_output.txt

clean:
	rm assembler out.txt
