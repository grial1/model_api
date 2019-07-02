PROG=example
TEST=debug
SHARED=libInputDataset.so
OBJECTS=Dataset.o InputDataset.o

INCLUDE= -Iinclude/ -I/usr/include/python3.6m/
CATCH_INCLUDE= $(INCLUDE) -Iinclude/test
LIB= -lpython3.6m -lboost_python3-py36 -lboost_numpy3-py36
CXXFLAGS= $(INCLUDE) -std=c++11
CXX=g++

.PHONY: $(PROG).cc

all: $(OBJECTS) $(SHARED)

example: $(PROG).bin

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

$(PROG).bin: $(PROG).cc
	$(CXX) src/$< $(CXXFLAGS) $(LIB) -lInputDataset -o $@
	@if [ "$(EXAMPLE)" = "0" ];\
	then\
		$(MAKE) -C src/module_1;\
	elif [ "$(EXAMPLE)" = "1" ];\
	then\
		$(MAKE) -C src/module_2;\
	fi

clean:
	rm -rf obj/*.o
	rm -rf *.bin
	rm -rf *.so
	rm -rf build
	$(MAKE) -C src/module_1 clean
	$(MAKE) -C src/module_2 clean

$(TEST):$(PROG).cc
	$(CXX) -g -c -o obj/Dataset.o src/Dataset.cc $(CXXFLAGS)
	$(CXX) -g -c -o obj/InputDataset.o src/InputDataset.cc $(CXXFLAGS)
	$(CXX) -g -o $@.bin src/$< obj/Dataset.o obj/InputDataset.o $(LIB) $(CXXFLAGS)
	gdb ./$(TEST).bin

clean_debug:
	rm -rf $(TEST).bin
