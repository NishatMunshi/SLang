# directories
CUR_DIR  = $(notdir $(shell pwd))
HDR_DIR  = ./include
SRC_DIR  = ./src
OBJ_DIR  = ./build
EXE_DIR  = ./exec
TMP_DIRS = $(OBJ_DIR) $(EXE_DIR)

# file extentions
HDR_EXT = h
SRC_EXT = c
OBJ_EXT = o

# files
SRCS = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJS = $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/%.$(OBJ_EXT), $(SRCS))
HDRS = $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(HDR_DIR)/%.$(HDR_EXT), $(SRCS))

# target executable
TARGET = $(EXE_DIR)/slc

# compiler info
CXX           = gcc
CXX_STD       = c17
CXX_FLAGS     = -Wall -Wextra -Wpedantic -std=$(CXX_STD)

# linker stuff
LD       = $(CXX)

# rules to build everything
all: release
	@:

# build with debug info
debug: CXX_FLAGS += -DDEBUG -g
debug: $(TARGET)

# rule to compile the compiler
release: CXX_FLAGS += -DRELEASE -O3
release: $(TARGET)

# link
$(TARGET): $(OBJS)
	@echo [MAKE]: linking target executable $@
	@mkdir -p $(EXE_DIR); $(CXX) -o $@ $^

# compile
$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT) $(HDR_DIR)/%.$(HDR_EXT)
	@echo [MAKE]: compiling C source file $<
	@mkdir -p $(OBJ_DIR); $(CXX) $(CXX_FLAGS) -o $@ -c $<

# rule to clean the temporary directories
clean:
	@echo [MAKE]: cleaning temporary directories in $(CUR_DIR)
	@rm -rf $(TMP_DIRS)

.PHONY: all debug release clean