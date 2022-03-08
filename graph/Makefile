LAYOUT_ENGINE := fdp
FORMAT := svg

DEST := call.$(FORMAT) call-internal.$(FORMAT) include.$(FORMAT)

default: all

include.gv:
	. include_graph.sh

call.$(FORMAT): call.gv
	$(LAYOUT_ENGINE) $< -T$(FORMAT) > $@

call-internal.$(FORMAT): call-internal.gv
	$(LAYOUT_ENGINE) $< -T$(FORMAT) > $@

include.$(FORMAT): include.gv
	$(LAYOUT_ENGINE) $< -T$(FORMAT) > $@

all: $(DEST)

clean:
	rm -f $(DEST)

.PHONY: $(DEST) all clean
