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
#include "guid.h"
#include <curses.h>
#include <set>
#include <vector>

typedef std::set<OnscreenElement*, OnscreenElementPtrComp> ElementSet;

class Output{
    public:
        static Output& getInstance();

        void init(int w, int h, int offset);

        int w(){ return m_w; }
        int w(int w){ m_w = w; return m_w; }

        int h(){ return m_h; }
        int h(int h){ m_h = h; return m_h; }

        int offset(){ return m_offset; }
        int offset(int o){ m_offset = o; return m_offset; }

        void getCursorPosition(int &x, int &y);
        void setCursorPosition(int x, int y);

        void getGameWindowCursorPosition(int &x, int &y);
        void setGameWindowCursorPosition(int x, int y);

        void refreshGameWindow();
        void addElement(OnscreenElement *element);
        void removeElement(OnscreenElement *element);

    private:
        Output();
        Output(Output&);
        void operator=(Output const&);

        WINDOW *m_gameWindow;
        int m_w, m_h; /* width and height */
        int m_offset; /* # of chars from edge of screen */
        std::vector<char> lastScreen;
        ElementSet elements;
};

#endif /* ifndef OUTPUT_H */
