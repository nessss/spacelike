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
#include <curses.h>
#include <set>
#include <vector>

struct OutputOptions{
    int gameWindowW;
    int gameWindowH;
    int gameWindowX;
    int gameWindowY;
};

class Output{
    public:
        /** Get the instance @retval Output& */
        static Output& getInstance();

        /** Initialize with options @retval Output& */
        void init(const OutputOptions& options);

        int gameWindowW() const { return m_gameWindowW; }
        int gameWindowW(int w){ m_gameWindowW = w; return m_gameWindowW; }

        int gameWindowH() const { return m_gameWindowH; }
        int gameWindowH(int h){ m_gameWindowH = h; return m_gameWindowH; }

        int gameWindowX() const { return m_gameWindowX; }
        int gameWindowX(int x){ m_gameWindowX = x; return m_gameWindowX; }

        int gameWindowY() const { return m_gameWindowY; }
        int gameWindowY(int y){ m_gameWindowY = y; return m_gameWindowY; }

        void getCursorPosition(int &x, int &y);
        void setCursorPosition(int x, int y);

        void getGameWindowCursorPosition(int &x, int &y);
        void setGameWindowCursorPosition(int x, int y);

        void refreshGameWindow();
        void setZone(Zone* zone);

    private:
        Output();
        Output(Output&);
        void operator=(Output const&);

        WINDOW* m_gameWindow;
        const Zone* m_zone;

        int m_gameWindowW, m_gameWindowH; /* width and height */
        int m_gameWindowX, m_gameWindowY; /* upper-left corner */

        std::vector<char> lastScreen;
        Zone::ElementSet elements;
};

#endif /* ifndef OUTPUT_H */
