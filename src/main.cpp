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
#include "item.h"

int main(int argc, char *argv[]){

    Input& input = Input::getInstance();

    Player player(1, 1);
    player.symbol('@');

    OutputOptions options;
    options.gameWindowW = 40;
    options.gameWindowH = 20;
    options.gameWindowX = 3;
    options.gameWindowY = 2;
    options.inventoryW = 20;

    Output &output = Output::getInstance();

    Zone zone(40, 20);

    zone.loadMap("../data/test.map");


    output.init(options, &zone);
    output.zone(&zone);

    zone.addElement(&player);

    Output::getInstance().gameWindowCursorPosition(player.x(), player.y());

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
