# directories
CUR_DIR  = $(notdir $(shell pwd))
SRC_DIR  = ./src
ASS_DIR  = ./ass
OBJ_DIR  = ./obj
EXE_DIR  = ./exe
TMP_DIRS = $(ASS_DIR) $(OBJ_DIR) $(EXE_DIR)

# file extensions
SRC_EXT = sl
ASS_EXT = s
OBJ_EXT = o

# files
SRCS = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
ASSS = $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(ASS_DIR)/%.$(ASS_EXT), $(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/%.$(OBJ_EXT), $(SRCS))

# target executable
TARGET = $(EXE_DIR)/example

.SECONDARY: $(ASSS)

# compiler info
SLC = ../slc/exe/slc

# assembler info
ASS       = nasm
ASS_FLAGS = -felf64

# linker info
LD = ld

# rules to run fly on an example file
all: $(TARGET)
	@:

# link
$(TARGET): $(OBJS)
	@echo [MAKE]: linking target executable $@
	@mkdir -p $(EXE_DIR); $(LD) -o $@ $^

# assemble
$(OBJ_DIR)/%.$(OBJ_EXT): $(ASS_DIR)/%.$(ASS_EXT)
	@echo [MAKE]: building object file $@
	@mkdir -p $(OBJ_DIR); $(ASS) $(ASS_FLAGS) -o $@ $<

# compile
$(ASS_DIR)/%.$(ASS_EXT): $(SRC_DIR)/%.$(SRC_EXT)
	@echo [MAKE]: building assembly file $@
	@mkdir -p $(ASS_DIR); $(SLC) $< $@

# rule to run the target
run: $(TARGET)
	@echo [MAKE]: running target executable $<
	@$<
	@echo $$?

# rule to clean the temporary directories
clean:
	@echo [MAKE]: cleaning temporaries in $(CUR_DIR)
	@rm -rf $(TMP_DIRS)

.PHONY: all run clean