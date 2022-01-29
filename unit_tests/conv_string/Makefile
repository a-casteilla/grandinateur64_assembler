default: run

assembler:
	cd ../.. ;\
	mv config.h config.h.bak ;\
	sed "s/\/\/#define unit_test_of_convert_literal/#define \
	unit_test_of_convert_literal/" < config.h.bak > config.h ;\
	make clean ; \
	make ; \
	mv assembler tests/convert_literal/ ; \
	make clean ; \
	mv config.h.bak config.h

run: assembler
	./assembler < input.txt > out.txt
	vim out.txt

clean:
	rm assembler out.txt
