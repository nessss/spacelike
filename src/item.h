#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "onscreen_element.h"

using namespace std;

class Item : OnscreenElement{
    public:
        Item(string name="", string desc="");
        string name(){ return m_name; }
        string name(string name){ m_name = name; return m_name; }

        string description(){ return m_desc; }
        string description(string desc){ m_desc = desc; return m_desc; }

        int weight(){ return m_weight; }
        int weight(int weight){ m_weight = weight; return m_weight; }

    private:
        string m_name;
        string m_desc;
        int m_weight;
};

#endif /* ifndef ITEM_H */
