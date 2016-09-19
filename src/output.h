/* Screen output handler.
 * Renders registered OnscreenElements, considering relative
 * depth. All curses output functions should be confined to
 * this class, allowing the rest of the program to use the
 * otherwise conventional (x, y) coordinate system rather than
 * curses' (y, x) system.
 */

#ifndef OUTPUT_H
#define OUTPUT_H 

#include "onscreen_element.h"
#include "zone.h"
#include "guid.h"
#include "item.h"
#include <curses.h>
#include <set>
#include <vector>

struct OutputOptions{
    int gameWindowW;
    int gameWindowH;
    int gameWindowX;
    int gameWindowY;

    int inventoryW;
};

class Output{
    public:
        /** Get the instance @retval Output& */
        static Output& getInstance();

        /** Initialize with options @retval Output& */
        void init(const OutputOptions& options);

        OutputOptions options;

        Zone* zone();
        Zone* zone(Zone* zone);

        void cursorPosition(int* x, int* y);
        void cursorPosition(const int x, const int y);

        void gameWindowCursorPosition(int* x, int* y);
        void gameWindowCursorPosition(const int x, const int y);

        void refreshGameWindow();
        void displayInventory(std::set<Item*> items);

    private:
        Output();
        Output(Output&);
        void operator=(Output const&);

        WINDOW* m_gameWindow;
        WINDOW* m_inventory;
        Zone* m_zone;

        Zone::ElementSet elements;
};

#endif /* ifndef OUTPUT_H */
