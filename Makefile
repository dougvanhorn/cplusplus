# A makefile.

CXXFLAGS = -std=c++17 -g -Wall
SOURCES = foo.cpp random.cpp


# The first target is the default
main: $(SOURCES)
	g++ $(CXXFLAGS) -o main $(SOURCES)


# Run with `make hello`
hello:
	echo "Hello, world"

