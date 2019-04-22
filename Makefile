TARGETS = all clean

SUBDIRS = $(wildcard */.)

$(TARGETS): $(SUBDIRS)
	@echo Done.

$(SUBDIRS):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: all clean $(TARGETS) $(SUBDIRS)
