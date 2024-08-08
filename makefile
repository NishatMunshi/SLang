SUBMAKE_DIRS = $(dir $(shell find -mindepth 2 -maxdepth 10 -type f -name "makefile"))

all:
	@$(MAKE) --no-print-directory -C docs/grammar
	@$(MAKE) --no-print-directory -C slc
	@$(MAKE) --no-print-directory -C example

clean:
	@for dir in $(SUBMAKE_DIRS); do $(MAKE) --no-print-directory -C $$dir clean; done

.PHONY: all clean
