SUBMAKE_DIRS = $(dir $(wildcard */makefile))

all:
	@$(MAKE) --no-print-directory -C docs
	@$(MAKE) --no-print-directory -C slc
	@$(MAKE) --no-print-directory -C example

clean:
	@for dir in $(SUBMAKE_DIRS); do $(MAKE) --no-print-directory -C $$dir clean; done

.PHONY: all clean
