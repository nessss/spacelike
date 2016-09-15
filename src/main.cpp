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

    Player player;
    Input input;

    OutputOptions options;
    options.gameWindowW = 40;
    options.gameWindowH = 20;
    options.gameWindowX = 3;
    options.gameWindowY = 3;

    Output &output = Output::getInstance();
    output.init(options);

    Zone zone(40, 20);

    output.setZone(&zone);

    std::list<FloorTile> floorTiles;

    for(int x = 0; x < zone.w(); x++){
        for(int y = 0; y < zone.h(); y++){
            floorTiles.emplace_front(x, y);
            zone.addElement(&(floorTiles.front()));
        }
    }

    input.focusedActor(&player);
    zone.addElement(&player);
    player.zone(&zone);

    output.refreshGameWindow();

    while(true){
        input.processInput();

        output.refreshGameWindow();
    }

    Application::finish(0);
}
