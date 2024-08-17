# directories
CUR_DIR  = $(notdir $(shell pwd))
HDR_DIR  = ./include
SRC_DIR  = ./src
OBJ_DIR  = ./build
BIN_DIR  = ./bin
TMP_DIRS = $(OBJ_DIR) $(BIN_DIR)

# file extentions
HDR_EXT = h
SRC_EXT = c
OBJ_EXT = o

# files
SRCS = $(shell find -type f -name *.$(SRC_EXT))
OBJS = $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/%.$(OBJ_EXT), $(SRCS))
HDRS = $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(HDR_DIR)/%.$(HDR_EXT), $(SRCS))

# target executable
TARGET = $(BIN_DIR)/slc

# compiler info
CXX           = gcc
CXX_STD       = c17
CXX_FLAGS     = -Wall -Wextra -Wpedantic -std=$(CXX_STD)
INCLUDE_PATHS = -I$(HDR_DIR)

# linker stuff
LD = $(CXX)

# rules to build everything
all: dirs release

DIRS = $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(shell find $(SRC_DIR) -type d))
dirs:
	@echo [MAKE]: making necessary directories
	@mkdir -p $(DIRS) $(BIN_DIR)

# build with debug info
debug: CXX_FLAGS += -DSLC_DEBUG_BUILD -g
debug: $(TARGET)

# rule to compile the compiler
release: CXX_FLAGS += -DSLC_RELEASE_BUILD -O3
release: $(TARGET)

# link
$(TARGET): $(OBJS)
	@echo [MAKE]: linking target executable $@
	@$(LD) -o $@ $^

# compile
$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT) $(HDR_DIR)/%.$(HDR_EXT)
	@echo [MAKE]: building object file $@
	@$(CXX) $(CXX_FLAGS) -o $@ -c $< $(INCLUDE_PATHS)

# rule to clean the temporary directories
clean:
	@echo [MAKE]: cleaning temporaries in $(CUR_DIR)
	@rm -rf $(TMP_DIRS)

.PHONY: all dirs debug release clean