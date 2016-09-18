#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <assert.h>
#include <list>
#include <iostream>
#include <typeinfo>

#include "application.h"
#include "input.h"
#include "output.h"
#include "zone.h"
#include "player.h"
#include "floor_tile.h"
#include "item.h"

int main(int argc, char *argv[]){

    Player player;
    player.symbol('h');

    Input& input = Input::getInstance();

    OutputOptions options;
    options.gameWindowW = 40;
    options.gameWindowH = 20;
    options.gameWindowX = 3;
    options.gameWindowY = 3;

    Output &output = Output::getInstance();
    output.init(options);

    Zone zone(40, 20);

    output.zone(&zone);

    std::list<FloorTile> floorTiles;

    for(int x = 0; x < zone.w(); x++){
        for(int y = 0; y < zone.h(); y++){
            floorTiles.emplace_front(x, y);
            zone.addElement(&(floorTiles.front()));
        }
    }

    zone.addElement(&player);

    Item slimeMold;
    zone.addElement(&slimeMold);
    slimeMold.name("Slime mold");
    slimeMold.description("A tasty, juicy, nutritious slime mold. Your mouth waters just thinking about it.");
    slimeMold.move(12, 14);

    output.refreshGameWindow();

    while(true){
        input.processInput();

        output.refreshGameWindow();
    }

    Application::finish(0);
}
