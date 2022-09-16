# A makefile.

random: random.cpp
	g++ -std=c++17 random.cpp -o random

hello:
	echo "Hello, world"

