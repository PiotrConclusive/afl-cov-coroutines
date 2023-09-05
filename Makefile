CXX = afl-g++
CXXFLAGS = -std=c++20 -fprofile-arcs -ftest-coverage

SOURCES = main.cpp
EXECUTABLE = coroutine_example

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
