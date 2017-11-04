all:
	g++ src/*.cpp -o b@rl -Iinclude -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall
