# rule to build everything
all: release

# directories
HDR_DIR  = ./include
SRC_DIR  = ./src
OBJ_DIR  = ./build
BIN_DIR  = ./bin

# target executable
TARGET = $(BIN_DIR)/slc

# build with debug info
debug: CXX_FLAGS += -DSLC_DEBUG_BUILD -g
debug: build_dirs $(TARGET)

# rule to compile the compiler
release: CXX_FLAGS += -DSLC_RELEASE_BUILD -O3
release: build_dirs $(TARGET)

# make dirs ---------------------------------------------------------------------
BLD_DIRS = $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(shell find $(SRC_DIR) -type d))

# make necessary directory structure inside $(OBJ_DIR)
build_dirs:
	@echo [MAKE]: making necessary directories
	@mkdir -p $(BLD_DIRS) $(BIN_DIR)

# ---------------------------------------------------------------------------------

# compile ------------------------------------------------------------------------
# compiler info
CXX           = gcc
CXX_STD       = c17
CXX_FLAGS     = -Wall -Wextra -Wpedantic -Werror -std=$(CXX_STD)
INCLUDE_PATHS = -I$(HDR_DIR)

# file extentions
HDR_EXT = h
SRC_EXT = c
OBJ_EXT = o

# source files
SRCS = $(shell find -type f -name *.$(SRC_EXT))

# rule to compile source files into object files
$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT) $(HDR_DIR)/%.$(HDR_EXT)
	@echo [MAKE]: building object file $@
	@$(CXX) $(CXX_FLAGS) -o $@ -c $< $(INCLUDE_PATHS)

# ---------------------------------------------------------------------------------

# link ----------------------------------------------------------------------------
# linker info
LD = $(CXX)

# object files
OBJS = $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/%.$(OBJ_EXT), $(SRCS))

# rule to link object files into target executable
$(TARGET): $(OBJS)
	@echo [MAKE]: linking target executable $@
	@$(LD) -o $@ $^

# ---------------------------------------------------------------------------------

# clean ---------------------------------------------------------------------------
CUR_DIR  = $(notdir $(shell pwd))
TMP_DIRS = $(OBJ_DIR) $(BIN_DIR)

# rule to clean the temporary directories
clean:
	@echo [MAKE]: cleaning temporaries in $(CUR_DIR)
	@rm -rf $(TMP_DIRS)

.PHONY: all debug release build_dirs clean

# ---------------------------------------------------------------------------------
