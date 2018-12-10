SRC=src/*.cpp
OBJ=strx_manip.o strx_format.o
PNAME=stringx
SAMPLESRC=samples/main.cpp
TESTS=tests/cpp-test/test_suite.cpp tests/run.cpp
INCLUDES=-Iinclude
CLANG= -std=c++14
LIB=-Llib -l$(PNAME)
CC=@g++ $(CLANG)

TLOG=_tmp.log
FAILCATCH=2> $(TLOG) || ( printf "\e[31mFAILED\e[0m\n" && cat $(TLOG) && exit 1 )


library: $(SRC)
	@printf "\e[33mBUILD LIBRARY...\e[0m"
	$(CC) $(INCLUDES) -c $(SRC)
	@mkdir -p lib
	@printf "\e[32mDONE\n\e[33mARCHIVE LIBRARY...\e[0m"
	@ar rcs lib/lib$(PNAME).a $(OBJ)
	@printf "\e[32mDONE\n\e[0m"
	@rm $(OBJ)
	
sample: library $(SAMPLESRC)
	@printf "\e[33mBUILD SAMPLE...\e[0m"
	$(CC) $(INCLUDES) $(LIB) $(SAMPLESRC) -o $(PNAME)-sample.o $(FAILCATCH)
	@printf "\e[32mDONE\n\e[0m"

test: library $(TESTS)
	@printf "\e[33mBUILD TEST...\e[0m"
	$(CC) $(INCLUDES) $(LIB) $(TESTS) -o $(PNAME)-tests.o $(FAILCATCH)
	@printf "\e[32mDONE\n\e[33mRUN TEST...\e[0m\n"
	@./$(PNAME)-tests.o -v
	@rm $(TLOG)
	
clean:
	@printf "\e[33mCLEANING BUILD FILES\e[0m\n\t"
	rm -Rf lib/ $(PNAME)-sample.o $(PNAME)-tests.o $(OBJ) || true
