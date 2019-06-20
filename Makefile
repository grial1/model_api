PROG=example
#TEST=SimpleJsonParserTest
INCLUDE= -Iinclude/ -I/usr/include/python3.6m/
CATCH_INCLUDE= $(INCLUDE) -Iinclude/test
CXXFLAGS= $(INCLUDE) -std=c++11
CXX=g++

.PHONY:$(PROG).cc #$(TEST).cc

all:$(PROG).o $(PROG).bin

Dataset:
	$(CXX) -c -o obj/$@.o src/$@.cc $(CXXFLAGS)

InputDataset:
	$(CXX) -c -o obj/$@.o src/$@.cc $(CXXFLAGS)

$(PROG).o:$(PROG).cc
	$(CXX) -c -o obj/$@ src/$< $(CXXFLAGS)

$(PROG).bin:$(PROG).o
	$(CXX) -o $@ obj/$< $(CXXFLAGS)

clean:
	rm -rf obj/*.o

run:
	./$(PROG).bin

debug:$(PROG).cc
	$(CXX) -g -o debug.bin src/$< $(CXXFLAGS)
	gdb ./debug.bin

clean_debug:
	rm -rf debug.bin
	#rm -rf $(TEST).bin

#test:$(TEST).bin run_test
	
#$(TEST).bin:$(TEST).cc
	#$(CXX) -o $@ src/$< $(CATCH_INCLUDE)

#run_test:$(TEST).bin
#	./$<