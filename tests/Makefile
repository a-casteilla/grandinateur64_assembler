SUBDIRS := $(wildcard */.)

testall:
	for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir; \
	done

buildall:
	for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir test; \
	done

cleanall:
	for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir clean; \
	done
