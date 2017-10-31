all:
	g++ src/*.cpp -o brl -Iinclude -L. -ltcodxx -Wl,-rpath=. -Wall
