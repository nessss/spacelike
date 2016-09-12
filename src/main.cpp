#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <assert.h>
#include <list>
#include <iostream>

#include "main.h"
#include "application.h"
#include "input.h"
#include "output.h"
#include "player.h"
#include "floor_tile.h"

int main(int argc, char *argv[]){

    int rows = 20;
    int cols = 40;
    int gameWindowOffset = 3;

    Player player;
    Input input;
    Output &output = Output::getInstance();
    output.init(cols, rows, gameWindowOffset);
    std::list<FloorTile> floorTiles;

    for(int x = 0; x < cols; x++){
        for(int y = 0; y < rows; y++){
            floorTiles.emplace_front(x, y);
            output.addElement(&(floorTiles.front()));
        }
    }

    input.setFocusedActor(&player);
    output.addElement(&player);


    output.refreshGameWindow();

    while(true){
        input.processInput();

        output.refreshGameWindow();
    }

    Application::finish(0);
}

