default: run

assembler:
	cd ../.. ;\
	mv config.h config.h.bak ;\
	sed "s/\/\/#define unit_test_of_parent_scope/#define \
	unit_test_of_parent_scope/" < config.h.bak > config.h ;\
	make clean ; \
	make ; \
	mv assembler tests/parent_scope/ ; \
	make clean ; \
	mv config.h.bak config.h

run: assembler
	./assembler < input.txt > out.txt
	vimdiff out.txt expected_output.txt

clean:
	rm assembler out.txt
