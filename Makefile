EXENAME = encounters
OBJS = data_reader.o trees/avl_tree.o trees/kd_tree.o
HEADERFILES = data_reader.h trees/avl_tree.h trees/kd_tree.h
SOURCEFILES = data_reader.cpp trees/avl_tree.cpp trees/kd_tree.cpp
SUBSEQUENTFILES = data_reader.cpp data_reader.h trees/avl_tree.cpp trees/avl_tree.h trees/kd_tree.cpp trees/kd_tree.h 
TESTOBJS = tests/test_makefile.o
TESTFILES = tests/test_makefile.cpp

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) main.o $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp $(HEADERFILES)
	$(CXX) $(CXXFLAGS) main.cpp

encounters.o : $(SUBSEQUENTFILES)
	$(CXX) $(CXXFLAGS) $(SOURCEFILES)

test: output_msg catchmain.o $(TESTFILES)
	$(LD) catchmain.o $(TESTOBJS) $(OBJS) $(LDFLAGS) -o test

catchmain.o : catch/catchmain.cpp catch/catch.hpp
	$(CXX) $(CXXFLAGS) catch/catchmain.cpp

clean :
	-rm -f *.o $(EXENAME) test
