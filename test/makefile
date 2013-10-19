INCLUDE:= -Iinclude -I../include

LIBS:=  -L.. -lRLlib

SRC:= $(wildcard src/*.cc)
OBJ:= $(SRC:src/%.cc=bin/%.o)

MAINS:= RunTests

MAINSOBJ:= $(MAINS:%=bin/%.o)
LIBOBJ:= ../libRLlib.a

CCFLAGS:=  -pthread -Wall -fPIC -O3

CC:= g++

.PHONY: clean

all: bin $(MAINS) $(LIBOBJ)

bin:
	@echo Making directory for binaries...
	@mkdir -p bin

makerun: all
	@echo Running tests...
	@./RunTests

test: 
	@echo Compiling main test object...
	@$(MAKE) -C test makerun

include/ExistingTests.cff:
	@echo Creating list of existing tests...
	@./testlist_create.sh

$(MAINS): %: $(filter-out $(MAINSOBJ), $(OBJ)) include/ExistingTests.cff bin/%.o
	@echo Compiling $@
	$(CC) $(CCFLAGS) $(INCLUDE) $(filter-out include/ExistingTests.cff, $^) $(LIBS) -o $@  


bin/%.o: src/%.cc include/%.hh include/ExistingTests.cff
	@echo Compiling $@
	@$(CC) $(CCFLAGS) $(INCLUDE) -c $< $(LIBS) -o $@


clean:
	@echo Cleaning up test directories...
	@rm -rf $(MAINS)
	@rm -rf bin/*
	@rm -rf include/ExistingTests.cff
	@find . -type f -name "*.o" -exec rm -f {} \;
	@find . -type f -name "*.a" -exec rm -f {} \;
	@find . -type f -name "*.d" -exec rm -f {} \;
	@find . -type f -name "*.of" -exec rm -f {} \;
	@find . -type f -name "*~" -exec rm -f {} \;
	@find . -type f -name "\#*\#" -exec rm -f {} \;
