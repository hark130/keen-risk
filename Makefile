##########################
###### INSTRUCTIONS ######
##########################
#
# 1. Save <YOUR_PRESENTATION>.rst file into the slides_raw directory
# 2. make
# 3. Open slides_built/<YOUR_PRESENTATION>_html/index.html in a web browser
# 4. Distrubute slides_archive/<YOUR_PRESENTATION>.zip as you see fit
#
# Global "constants" are defined in Makefile_constants
# Source: https://github.com/hark130/keen-risk
#


##########################
### MAKEFILE VARIABLES ###
##########################

### OS-DEPENDENT INCLUSION ###
ifeq ($(OS),Windows_NT)
include Makefile_windows
else
include Makefile_linux
endif

.PHONY: all compile clean validate


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
