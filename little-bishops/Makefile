all: main cheat

main: main.cpp
	g++ $< -o $@

cheat: cheat.cpp
	g++ $< -o $@

test: cheat
	./cheat < input
