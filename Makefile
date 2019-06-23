PROG=example
TEST=debug
OBJECTS=Dataset.o InputDataset.o

INCLUDE= -Iinclude/ -I/usr/include/python3.6m/
CATCH_INCLUDE= $(INCLUDE) -Iinclude/test
LIB= -lpython3.6m -lboost_python3-py36 -lboost_numpy3-py36
CXXFLAGS= $(INCLUDE) -std=c++11
CXX=g++

.PHONY:$(PROG).cc

all: $(OBJECTS) $(PROG).o $(PROG).bin

Dataset.o:
	$(CXX) -c -o obj/$@ src/Dataset.cc $(CXXFLAGS)

InputDataset.o: 
	$(CXX) -c -o obj/$@ src/InputDataset.cc $(CXXFLAGS)

$(PROG).o:$(PROG).cc
	$(CXX) -c -o obj/$@ src/$< $(CXXFLAGS)

$(PROG).bin: $(PROG).o
	$(CXX) -o $@ obj/Dataset.o obj/InputDataset.o obj/$< $(LIB) $(CXXFLAGS)

clean:
	rm -rf obj/*.o
	rm -rf *.bin

run:
	./$(PROG).bin

$(TEST):$(PROG).cc
	$(CXX) -g -c -o obj/Dataset.o src/Dataset.cc $(CXXFLAGS)
	$(CXX) -g -c -o obj/InputDataset.o src/InputDataset.cc $(CXXFLAGS)
	$(CXX) -g -o $@.bin src/$< obj/Dataset.o obj/InputDataset.o $(LIB) $(CXXFLAGS)
	gdb ./$(TEST).bin

clean_debug:
	rm -rf $(TEST).bin
