default: run

assembler:
	cd ../.. ;\
	mv config.h config.h.bak ;\
	sed "s/\/\/#define unit_test_of_align_and_is_a_power_of_two/#define \
	unit_test_of_align_and_is_a_power_of_two/" < config.h.bak > config.h ;\
	make clean ; \
	make ; \
	mv assembler tests/align_and_is_a_power_of_two/ ; \
	make clean ;
	mv config.h.bak config.h

run: assembler
	./assembler < input.txt > out.txt
	vimdiff out.txt expected_output.txt

clean:
	rm assembler out.txt out_error.txt
