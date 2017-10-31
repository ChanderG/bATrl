all:
	g++ src/*.cpp -o brl -Iinclude -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall
