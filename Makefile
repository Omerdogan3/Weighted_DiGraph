TARGET = test
LIBS =
HEADERS = Graph.h
OBJECTS = Graph.o test.o
CXX = g++
CXX_FLAGS = -g -Wall -std=c++11 -O3

.PHONY: default all clean

default: $(TARGET)
all: default

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
