objects = main.o player.o floor_tile.o
flags = -std=c++11

all: $(objects)
	mkdir -p ../build
	cd ../build;\
	g++ $(flags) $(objects) -o spacelike -lncurses

main.o: main.cpp
	g++ $(flags) -c main.cpp -o ../build/main.o

player.o: player.cpp
	g++ $(flags) -c player.cpp -o ../build/player.o

floor_tile.o: floor_tile.cpp
	g++ $(flags) -c floor_tile.cpp -o ../build/floor_tile.o

clean:
	-rm -r ../build/* 2> /dev/null
