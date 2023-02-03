##########################
###### INSTRUCTIONS ######
##########################
#
# 1. Save <YOUR_PRESENTATION>.rst file into the slides_raw directory
# 2. make
# 3. Open slides_built/<YOUR_PRESENTATION>_html/index.html in a web browser
# 4. Distrubute slides_archive/<YOUR_PRESENTATION>.zip as you see fit
#
# Source: https://github.com/hark130/keen-risk
#


##########################
### MAKEFILE VARIABLES ###
##########################

### OS-DYNAMIC VARIABLES ###
# $(CHECK) - Checkmark
CHECK :=
ifeq ($(OS),Windows_NT)
include Makefile_windows
else
# This section assumes Linux
include Makefile_linux
endif

.PHONY: all compile clean validate

### HOVERCRAFT ARGUMENTS ###
HC_ARGS = --slide-numbers

### MAKEFILE ARGUMENTS ###
MF_ARGS = --no-print-directory
CALL_MAKE = @$(MAKE) $(MF_ARGS)

### DIRECTORIES ###
# Relative path to the directory holding the rst source files
RAW_DIR = slides_raw
# Relative path to the directory to store the "compiled" HTML files
BUILD_DIR = slides_built
# Relative path to the directory to store the zip-formatted HTML archives
ARCHIVE_DIR = slides_archive

### FILE EXTENSIONS ###
RAW_FILE_EXT = .rst
HTML_DIR_EXT = _html
ARCHIVE_FILE_EXT = .zip

### DYNAMIC VARIABLES ###
# All .rst filenames found in RAW_DIR
# RAW_FILENAMES:=$(shell cd $(RAW_DIR); $(LSD) *$(RAW_FILE_EXT))
# RAW_FILENAMES = 00_00-EXAMPLES.rst 00_01-TEMPLATE.rst 
# All RAW_FILENAMES with the file extension stripped
# PRESENTATIONS := $(basename $(RAW_FILENAMES))
# Relative directory names for the per-presentation BUILD_DIR directories
# HTML_DIRS := $(addprefix $(BUILD_DIR)$(SEP),$(addsuffix $(HTML_DIR_EXT),$(PRESENTATIONS)))
# Relative filenames for the pre-presentation archive files
# ARCHIVE_FILES := $(addprefix $(ARCHIVE_DIR)$(SEP),$(addsuffix $(ARCHIVE_FILE_EXT),$(PRESENTATIONS)))
# FILES := $(foreach DIR,$(RAW_DIR),$(wildcard $(DIR)\*))

ARCHIVE_DIR_WIN := $(ARCHIVE_DIR)*

##########################
##### MAKEFILE RULES #####
##########################
all:
	$(CALL_MAKE) validate
	$(CALL_MAKE) clean
	$(CALL_MAKE) compile

compile:
	@echo ""
	@echo "COMPILING"
	$(CALL_MAKE) _compile

clean:
	@echo ""
	@echo "CLEANING"
	$(CALL_MAKE) _clean

validate:
	@echo ""
	@echo "VALIDATING"
	$(CALL_MAKE) _validate
