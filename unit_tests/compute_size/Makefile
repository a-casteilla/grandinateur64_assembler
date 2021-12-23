default: run

assembler:
	cd ../.. ;\
	mv config.h config.h.bak ;\
	sed "s/\/\/#define unit_test_of_compute_size/#define \
	unit_test_of_compute_size/" < config.h.bak > config.h ;\
	make clean ; \
	make ; \
	mv assembler tests/compute_size/ ; \
	make clean ; \
	mv config.h.bak config.h

run: assembler
	./assembler < input.txt > out.txt
	./assembler < input_error.txt 2> out_error.txt > /dev/null
	vimdiff out.txt expected_output.txt
	vimdiff out_error.txt expected_output_error.txt

clean:
	rm assembler out.txt out_error.txt
