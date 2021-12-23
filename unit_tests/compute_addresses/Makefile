default: run

assembler:
	cd ../.. ;\
	mv config.h config.h.bak ;\
	sed "s/\/\/#define unit_test_of_compute_addresses/#define \
	unit_test_of_compute_addresses/" < config.h.bak > config.h ;\
	make clean ; \
	make ; \
	mv assembler tests/compute_addresses/ ; \
	make clean ; \
	mv config.h.bak config.h

run: assembler
	./assembler < input.txt > out.txt
	./assembler < input_error_1.txt 2> out_error_1.txt > /dev/null
	./assembler < input_error_2.txt 2> out_error_2.txt > /dev/null
	./assembler < input_error_3.txt 2> out_error_3.txt > /dev/null
	vimdiff out.txt expected_output.txt
	vimdiff out_error_1.txt expected_output_error_1.txt
	vimdiff out_error_2.txt expected_output_error_2.txt
	vimdiff out_error_3.txt expected_output_error_3.txt

clean:
	rm assembler out.txt out_error_*.txt
