objects = main.o player.o

all: $(objects)
	mkdir -p ../build
	cd ../build;\
	g++ $(objects) -o spacelike -lncurses

main.o: main.cpp
	g++ -c main.cpp -o ../build/main.o

player.o: player.cpp
	g++ -c player.cpp -o ../build/player.o

clean:
	-rm -r ../build/* 2> /dev/null
