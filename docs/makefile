# directories
CUR_DIR  = $(notdir $(shell pwd))
SRC_DIR  = .
BLD_DIR  = .

# file extensions
SRC_EXT = tex
PDF_EXT = pdf

# files
SRCS   = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
TMPS   = $(shell ls -I"*.$(SRC_EXT)" -I"makefile")
TARGET = $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(BLD_DIR)/%.$(PDF_EXT), $(SRCS))

# compiler info
TEX       = latexmk
TEX_FLAGS = -synctex=1 -interaction=nonstopmode -file-line-error -pdf -outdir=$(BLD_DIR)

all: $(TARGET)

# compile
$(TARGET): $(SRCS)
	@echo [MAKE]: building LaTeX file $^ 
	@mkdir -p $(BLD_DIR); $(TEX) $(TEX_FLAGS) $^ > /dev/null

# rule to clean the temporary files
clean:
	@echo [MAKE]: cleaning temporary files in $(CUR_DIR)
	@rm -f $(TMPS)

.PHONY: all clean