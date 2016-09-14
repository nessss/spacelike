#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <assert.h>
#include <list>
#include <iostream>
#include <typeinfo>

#include "main.h"
#include "application.h"
#include "input.h"
#include "output.h"
#include "zone.h"
#include "player.h"
#include "floor_tile.h"

int main(int argc, char *argv[]){

    int gameWindowW = 40;
    int gameWindowH = 20;
    int gameWindowX = 3;
    int gameWindowY = 3;

    Player player;
    Input input;
    Output &output = Output::getInstance();

    output.init(
            gameWindowW,
            gameWindowH,
            gameWindowX,
            gameWindowY);

    Zone zone(40, 20);
    
    output.setZone(&zone);

    std::list<FloorTile> floorTiles;

    for(int x = 0; x < zone.w(); x++){
        for(int y = 0; y < zone.h(); y++){
            floorTiles.emplace_front(x, y);
            zone.addElement(&(floorTiles.front()));
        }
    }


    input.setFocusedActor(&player);
    zone.addElement(&player);

    output.refreshGameWindow();

    while(true){
        input.processInput();

        output.refreshGameWindow();
    }

    Application::finish(0);
}

