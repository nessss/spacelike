objects = main.o player.o floor_tile.o onscreen_element.o guid.o input.o output.o
flags = -std=c++11

all: $(objects) build
	cd ../build;\
	g++ $(flags) $(objects) -o spacelike -lncurses -framework CoreFoundation

build:
	mkdir -p ../build

main.o: main.cpp build
	g++ $(flags) -c main.cpp -o ../build/main.o

player.o: player.cpp build
	g++ $(flags) -c player.cpp -o ../build/player.o

floor_tile.o: floor_tile.cpp build
	g++ $(flags) -c floor_tile.cpp -o ../build/floor_tile.o

onscreen_element.o: onscreen_element.cpp guid.o build
	g++ $(flags) -c onscreen_element.cpp -o ../build/onscreen_element.o

guid.o: guid.cpp build
	g++ $(flags) -c guid.cpp -o ../build/guid.o -DGUID_CFUUID

input.o: input.cpp build
	g++ $(flags) -c input.cpp -o ../build/input.o

output.o: output.cpp build
	g++ $(flags) -c output.cpp -o ../build/output.o

clean:
	-rm -r ../build/* 2> /dev/null
