PROG=example
TEST=debug
SHARED=libInputDataset.so
OBJECTS=Dataset.o InputDataset.o

INCLUDE= -Iinclude/ -I/usr/include/python3.6m/
CATCH_INCLUDE= $(INCLUDE) -Iinclude/test
LIB= -lpython3.6m -lboost_python3-py36 -lboost_numpy3-py36
CXXFLAGS= $(INCLUDE) -std=c++11
CXX=g++

.PHONY:$(PROG).cc

all: model $(OBJECTS) $(SHARED)

example: $(PROG).o $(PROG).bin

model:
	$(MAKE) -C src/module

Dataset.o:
	$(CXX) -fPIC -c -o obj/$@ src/Dataset.cc $(CXXFLAGS)

InputDataset.o: 
	$(CXX) -fPIC -c -o obj/$@ src/InputDataset.cc $(CXXFLAGS)

$(SHARED):
	mkdir -p build/lib
	$(CXX) -fPIC obj/Dataset.o obj/InputDataset.o $(LIB) $(CXXFLAGS) -shared -o build/lib/$@

install:$(SHARED)
	cp build/lib/$< /usr/lib/
	ldconfig -v
	@echo "\n\tINSTALLATION FINISHED"

$(PROG).o:$(PROG).cc
	$(CXX) -c -o obj/$@ src/$< $(CXXFLAGS)

$(PROG).bin: $(PROG).o
	$(CXX) obj/$< $(CXXFLAGS) $(LIB) -lInputDataset -o $@
	./example.bin

clean:
	rm -rf obj/*.o
	rm -rf *.bin
	rm -rf *.so
	rm -rf build

run:
	./$(PROG).bin

$(TEST):$(PROG).cc
	$(CXX) -g -c -o obj/Dataset.o src/Dataset.cc $(CXXFLAGS)
	$(CXX) -g -c -o obj/InputDataset.o src/InputDataset.cc $(CXXFLAGS)
	$(CXX) -g -o $@.bin src/$< obj/Dataset.o obj/InputDataset.o $(LIB) $(CXXFLAGS)
	gdb ./$(TEST).bin

clean_debug:
	rm -rf $(TEST).bin
