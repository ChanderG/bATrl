all:
	g++ -std=c++11 src/*.cpp -o b@rl -Iinclude -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall
