### GNU MAKE VARIABLES ###
MAKE_ARGS = --no-print-directory
CALL_MAKE = @$(MAKE) $(MAKE_ARGS)

### COMPILER VARIABLES ###
CC = gcc
CFLAGS = -fpic

### PROJECT VARIABLES ###
SRC = src
INC = include
DST = dist

### SHARED OBJECT VARIABLES ###
LIB_NAME = harklemem
SO_NAME = lib$(LIB_NAME)
SO_FILE = $(SO_NAME)$(SO_EXT)
SO_FLAGS = -shared -Wl,-soname,$(SO_FILE).$(SO_VER_MAJ)
SO_EXT = .so
OBJ_EXT = .o
SRC_EXT = .c
OBJECTS = harklemem$(OBJ_EXT)
SO_VER_MAJ = 1
SO_VER_MIN = 0
SO_VER_MIC = 0

.PHONY: all 6-15-3

all:
	@echo "all"
	$(CALL_MAKE) 6-15-3

6-15-3: $(SO_NAME)$(SO_EXT)
	@echo "6-15-3"
# 	$(CALL_MAKE) $(SO_NAME)$(SO_EXT)

# %$(SO_EXT):
# 	@echo "HERE"

%$(SO_EXT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(DST)/$@ $(DST)/$^ $(SO_FLAGS)

%$(OBJ_EXT): %$(SRC_EXT)
	$(CC) $(CFLAGS) -c $(SRC)/$^ -o $(DST)/$@ -I $(INC)

%$(SRC_EXT):
	@echo "Verifying $(SRC)/$@"
	@if ! [ -f $(SRC)/$@ ] ; then echo "Unable to locate the $(SRC)/$@ file" >&2 && exit 2 ; fi
