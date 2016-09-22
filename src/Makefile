CC = g++ # compiler
LL = g++ # compiler
CFLAGS = -std=c++11 -Wall -I ../include/# compiler flags
LFLAGS = -lncurses # linker flags
GUIDFLAGS = 

objects = main.o application.o player.o floor_tile.o onscreen_element.o input.o output.o item.o zone.o tile.o guid.o

UNAME := $(shell uname -a)

ifneq (,$(findstring Cygwin, "$(UNAME)"))
	GUIDFLAGS = -DGUID_WINDOWS
	LFLAGS += -lOle32
endif

ifneq (,$(findstring Darwin, "$(UNAME)"))
	GUIDFLAGS = -DGUID_CFUUID
	LFLAGS += -framework CoreFoundation
endif

all: $(objects) link

build:
	mkdir -p ../build

link: build
	cd ../build;\
	g++ $(objects) -o spacelike $(LFLAGS)

main.o: main.cpp build
	g++ $(CFLAGS) -c main.cpp -o ../build/main.o

application.o: application.cpp build
	g++ $(CFLAGS) -c application.cpp -o ../build/application.o

onscreen_element.o: onscreen_element.cpp build
	g++ $(CFLAGS) -c onscreen_element.cpp -o ../build/onscreen_element.o

player.o: player.cpp build
	g++ $(CFLAGS) -c player.cpp -o ../build/player.o

item.o: item.cpp build
	g++ $(CFLAGS) -c item.cpp -o ../build/item.o

tile.o: tile.cpp build
	g++ $(CFLAGS) -c tile.cpp -o ../build/tile.o

door.o: door.cpp build
	g++ $(CFLAGS) -c door.cpp -o ../build/door.o

floor_tile.o: floor_tile.cpp build
	g++ $(CFLAGS) -c floor_tile.cpp -o ../build/floor_tile.o

zone.o: zone.cpp build
	g++ $(CFLAGS) -c zone.cpp -o ../build/zone.o

input.o: input.cpp build
	g++ $(CFLAGS) -c input.cpp -o ../build/input.o

output.o: output.cpp build
	g++ $(CFLAGS) -c output.cpp -o ../build/output.o

guid.o: guid.cpp build
	g++ $(CFLAGS) -c guid.cpp -o ../build/guid.o $(GUIDFLAGS)

clean:
	@-rm -rf ../build/*
