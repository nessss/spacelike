objects = main.o player.o floor_tile.o onscreen_element.o input.o output.o item.o
flags = -std=c++11

mac: $(objects) guid_mac.o build
	cd ../build;\
	g++ $(flags) $(objects) guid_mac.o -o spacelike -lncurses -framework CoreFoundation

cygwin: $(objects) guid_cyg.o build
	cd ../build;\
	g++ $(flags) $(objects) guid_cyg.o -o spacelike -lncurses -lOle32

build:
	mkdir -p ../build

main.o: main.cpp build
	g++ $(flags) -c main.cpp -o ../build/main.o

onscreen_element.o: onscreen_element.cpp build
	g++ $(flags) -c onscreen_element.cpp -o ../build/onscreen_element.o

player.o: player.cpp build
	g++ $(flags) -c player.cpp -o ../build/player.o

item.o: item.cpp build
	g++ $(flags) -c item.cpp -o ../build/item.o

floor_tile.o: floor_tile.cpp build
	g++ $(flags) -c floor_tile.cpp -o ../build/floor_tile.o

input.o: input.cpp build
	g++ $(flags) -c input.cpp -o ../build/input.o

output.o: output.cpp build
	g++ $(flags) -c output.cpp -o ../build/output.o

guid_mac.o: guid.cpp build
	g++ $(flags) -c guid.cpp -o ../build/guid_mac.o -DGUID_CFUUID

guid_cyg.o: guid.cpp build
	g++ $(flags) -c guid.cpp -o ../build/guid_cyg.o -DGUID_WINDOWS

clean:
	-rm -r ../build/* 2> /dev/null
