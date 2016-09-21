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
#include "tile.h"
#include "floor_tile.h"
#include "item.h"

int main(int argc, char *argv[]){

    Player player(1, 1);
    player.symbol('@');

    Input& input = Input::getInstance();

    OutputOptions options;
    options.gameWindowW = 40;
    options.gameWindowH = 20;
    options.gameWindowX = 3;
    options.gameWindowY = 2;
    options.inventoryW = 20;

    Output &output = Output::getInstance();

    Zone zone(40, 20);

    zone.loadMap("../data/test.map");

    std::cerr << "zone constructed" << std::endl;

    output.init(options, &zone);
    output.zone(&zone);
    std::cerr << "zone output set" << std::endl;

    zone.addElement(&player);
    Output::getInstance().gameWindowCursorPosition(player.x(), player.y());
    std::cerr << "player added to zone" << std::endl;

    Item slimeMold;
    zone.addElement(&slimeMold);
    std::cerr << "slime mold added to zone" << std::endl;

    slimeMold.name("Slime mold");
    slimeMold.description("A tasty, juicy, nutritious slime mold. Your mouth waters just thinking about it.");
    std::cerr << "slime mold info set" << std::endl;
    slimeMold.move(12, 14);
    std::cerr << "slime mold moved" << std::endl;

    output.refreshGameWindow();
    std::cerr << "game window refreshed" << std::endl;

    cerr << (*(zone.topmostElements()->begin()))->symbol() << std::endl;

    while(true){
        input.processInput();
        std::cerr << "input parsed" << std::endl;

        output.refreshGameWindow();
    }

    Application::finish(0);
}
