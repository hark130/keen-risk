##########################
### MAKEFILE VARIABLES ###
##########################

### INSTRUCTOR PRESENTATIONS ###
# Update this variable with the base filename (no file extension) whenever you add a new
# presentation source file to the RAW_DIR.
PRESENTATIONS = \
	00_00-EXAMPLES \
	00_01-TEMPLATE

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
# RST_FILES = $(addprefix $(RAW_DIR)/,$(addsuffix $(RAW_FILE_EXT),$(PRESENTATIONS)))
ARCHIVE_FILES = $(addprefix $(ARCHIVE_DIR)/,$(addsuffix $(ARCHIVE_FILE_EXT),$(PRESENTATIONS)))

### OS-DYNAMIC VARIABLES ###
# Where to shunt output to silence it?
NULL = /dev/null

######################
### MAKEFILE RULES ###
######################
all:
	$(CALL_MAKE) validate
	$(CALL_MAKE) clean
	$(CALL_MAKE) compile

.PHONY: all

bourbon_install:
	@cd $(RAW_DIR)
	@BOURBON_RESULTS="$(shell bourbon install)"  # Silence bourbon results
	@cd ..

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
	@echo "        TO DO: DON'T DO NOW... implement clean_build, agnostic of host OS"

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

$(BUILD_DIR)/%$(HTML_DIR_EXT)/: $(RAW_DIR)/%$(RAW_FILE_EXT)
	@echo "    Building "$@" from "$^
	$(CALL_MAKE) bourbon_install
	@mkdir $@
	@hovercraft $(HC_ARGS) $^ $@
