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

### OS-DYNAMIC VARIABLES ###
# Where to shunt output to silence it?
NULL = /dev/null
# What is the command to list directory contents?
LSD = ls

### DYNAMIC VARIABLES ###
# All .rst filenames found in RAW_DIR
RAW_FILENAMES=$(shell cd $(RAW_DIR); $(LSD) *$(RAW_FILE_EXT))
# All RAW_FILENAMES with the file extension stripped
PRESENTATIONS=$(basename $(RAW_FILENAMES))
# Relative directory names for the per-presentation BUILD_DIR directories
HTML_DIRS = $(addprefix $(BUILD_DIR)/,$(addsuffix $(HTML_DIR_EXT),$(PRESENTATIONS)))
# Relative filenames for the pre-presentation archive files
ARCHIVE_FILES = $(addprefix $(ARCHIVE_DIR)/,$(addsuffix $(ARCHIVE_FILE_EXT),$(PRESENTATIONS)))


##########################
##### MAKEFILE RULES #####
##########################
all:
	$(CALL_MAKE) validate
	$(CALL_MAKE) clean
	$(CALL_MAKE) compile

.PHONY: all

bourbon_install:
	@BOURBON_RESULTS="$(shell cd $(RAW_DIR); bourbon install)"  # Silence bourbon results

compile:
	@echo
	@echo "COMPILING"
	$(CALL_MAKE) _compile

_compile: $(foreach ARCHIVE_FILE, $(ARCHIVE_FILES), $(ARCHIVE_FILE))

clean:
	@echo
	@echo "CLEANING"
	$(CALL_MAKE) clean_build
	$(CALL_MAKE) clean_archive

clean_archive:
	@echo "    Cleaning "$(ARCHIVE_DIR)" directory"
	@$(foreach ARCHIVE_FILE, $(ARCHIVE_FILES), $(RM) $(ARCHIVE_FILE))

clean_build:
	@echo "    Cleaning "$(BUILD_DIR)" directory"
	@$(foreach HTML_DIR, $(HTML_DIRS), $(RM) -r $(HTML_DIR))

validate:
	@echo
	@echo "VALIDATING"
	$(CALL_MAKE) validate_bourbon
	$(CALL_MAKE) validate_hovercraft

validate_bourbon:
	@echo "    Validating bourbon"
	@bourbon --version > $(NULL)  # Tests the command before printing the version
	@BOURBON_VERSION="$(shell bourbon --version)"; echo "        [✓] "$$BOURBON_VERSION

validate_hovercraft:
	@echo "    Validating hovercraft"
	@hovercraft --version > $(NULL)  # Tests the command before printing the version
	@HOVERCRAFT_VERSION="$(shell hovercraft --version)"; echo "        [✓] "$$HOVERCRAFT_VERSION

$(ARCHIVE_DIR)/%$(ARCHIVE_FILE_EXT): $(BUILD_DIR)/%$(HTML_DIR_EXT)/
	@echo "    Archiving "$^" into "$@
	@cd $(BUILD_DIR); zip --quiet -r ../$@ $(*F)$(HTML_DIR_EXT)/

.PRECIOUS: $(BUILD_DIR)/%$(HTML_DIR_EXT)/  # Do NOT remove these intermediate files
$(BUILD_DIR)/%$(HTML_DIR_EXT)/: $(RAW_DIR)/%$(RAW_FILE_EXT)
	@echo "    Building "$@" from "$^
	$(CALL_MAKE) bourbon_install
	@mkdir $@
	@hovercraft $(HC_ARGS) $^ $@
