### GNU MAKE VARIABLES ###
MAKE_ARGS = --no-print-directory
CALL_MAKE = @$(MAKE) $(MAKE_ARGS)

### COMPILER VARIABLES ###
CC = gcc
CFLAGS = -fpic
AFLAGS = -fsanitize=address -g $(CFLAGS)

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
HDR_EXT = .h
OBJECTS = harklemem$(OBJ_EXT)
SO_VER_MAJ = 1
SO_VER_MIN = 0
SO_VER_MIC = 0

.PHONY: all 6-02-1 6-15-3 8-04-solution clean

all:
	$(CALL_MAKE) clean
	$(CALL_MAKE) 6-02-1
	$(CALL_MAKE) 6-15-3
	$(CALL_MAKE) 8-04-solution

6-02-1: $(SO_NAME)$(SO_EXT) owe_mem.c
	@echo "One With Everything memory"
	$(CC) $(SRC)/owe_mem.c -o $(DST)/owe_mem.bin -lharklemem

6-15-3: $(SO_NAME)$(SO_EXT)
	$(CC) $(CFLAGS) $(SRC)/main.c -o $(DST)/6-15-3.bin -lharklemem -I $(INC) -L $(DST)
	$(CC) $(AFLAGS) $(SRC)/main.c -o $(DST)/6-15-3_asan.bin -lharklemem -I $(INC) -L $(DST)

8-04-solution:
	$(CALL_MAKE) 8-04-1-solution

8-04-1-solution: $(DST)/8-04-hash_table-solution.o $(DST)/8-04-hash_functions.o
	$(CC) $(CFLAGS) $(SRC)/8-04-1-hash_table-main.c $^ -o $(DST)/8-04.bin -I $(INC) -L $(DST)
	$(CC) $(AFLAGS) $(SRC)/8-04-1-hash_table-main.c $^ -o $(DST)/8-04_asan.bin -I $(INC) -L $(DST)

%$(SO_EXT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(DST)/$@ $(DST)/$^ $(SO_FLAGS)
	cp $(DST)/$@ $(DST)/$(SO_FILE).$(SO_VER_MAJ).$(SO_VER_MIN).$(SO_VER_MIC)
	sudo cp $(INC)/$(LIB_NAME)$(HDR_EXT) /usr/include/
	sudo cp $(DST)/$(SO_FILE).$(SO_VER_MAJ).$(SO_VER_MIN).$(SO_VER_MIC) /lib
	sudo ln -f -s /lib/$(SO_FILE).$(SO_VER_MAJ).$(SO_VER_MIN).$(SO_VER_MIC) /lib/$(SO_FILE).$(SO_VER_MAJ)
	sudo ln -f -s /lib/$(SO_FILE).$(SO_VER_MAJ) /lib/$(SO_FILE)

$(DST)/%.o : $(SRC)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(INC)

%$(OBJ_EXT): %$(SRC_EXT)
	$(CC) $(CFLAGS) -c $(SRC)/$^ -o $(DST)/$@ -I $(INC)

%$(SRC_EXT):
	@echo "Verifying $(SRC)/$@"
	@if ! [ -f $(SRC)/$@ ] ; then echo "Unable to locate the $(SRC)/$@ file" >&2 && exit 2 ; fi

clean:
	@$(RM) $(DST)/*$(OBJ_EXT)
	@$(RM) $(DST)/*$(SO_EXT)
	@$(RM) $(DST)/*.bin
