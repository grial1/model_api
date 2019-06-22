PROG=example
OBJECTS=Dataset.o InputDataset.o

INCLUDE= -Iinclude/ -I/usr/include/python3.6m/
CATCH_INCLUDE= $(INCLUDE) -Iinclude/test
LIB= -lpython3.6m -lboost_python3-py36 -lboost_numpy3-py36
CXXFLAGS= $(INCLUDE) -std=c++11
CXX=g++

.PHONY:$(PROG).cc

all: $(OBJECTS) $(PROG).o $(PROG).bin

Dataset.o:
	$(CXX) -g -c -o obj/$@ src/Dataset.cc $(CXXFLAGS)

InputDataset.o: 
	$(CXX) -g -c -o obj/$@ src/InputDataset.cc $(CXXFLAGS)

$(PROG).o:$(PROG).cc
	$(CXX) -c -o obj/$@ src/$< $(CXXFLAGS)

$(PROG).bin: $(PROG).o
	$(CXX) -o $@ obj/Dataset.o obj/InputDataset.o obj/$< $(LIB) $(CXXFLAGS)

clean:
	rm -rf obj/*.o
	rm -rf *.bin

run:
	./$(PROG).bin

debug:$(PROG).cc
	$(CXX) -g -o $@.bin src/$< obj/Dataset.o obj/InputDataset.o $(LIB) $(CXXFLAGS)
	gdb ./debug.bin

clean_debug:
	rm -rf debug.bin
	#rm -rf $(TEST).bin

#test:$(TEST).bin run_test
	
#$(TEST).bin:$(TEST).cc
	#$(CXX) -o $@ src/$< $(CATCH_INCLUDE)

#run_test:$(TEST).bin
#	./$<