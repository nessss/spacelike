/* Screen output handler. */

#include "onscreen_element.h"
#include "guid.h"
#include <curses.h>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<Guid, OnscreenElement*> ElementMap;

class Output{
  public:
    Output(int w, int h, int offset = 3);

    int w(){ return m_w; }
    int w(int w){ m_w = w; return m_w; }

    int h(){ return m_h; }
    int h(int h){ m_h = h; return m_h; }

    int offset(){ return m_offset; }
    int offset(int o){ m_offset = o; return m_offset; }

    void getCursorPosition(int &x, int &y);
    void setCursonPosition(int x, int y);

    void refresh();
    void addElement(OnscreenElement*);

  private:
    int m_w, m_h; /* width and height */
    int m_offset; /* # of chars from edge of screen */
    std::vector<char> lastScreen;
    ElementMap elements;
};
