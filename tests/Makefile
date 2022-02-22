SUBDIRS := $(wildcard */.)

testall:
	for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir; \
	done

cleanall:
	for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean; \
	done
