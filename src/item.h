#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "onscreen_element.h"

using namespace std;

class Item : OnscreenElement{
    public:
        /** Construct item with optional name and description */
        Item(string name="", string desc="");

        /** Get name of item @retval string*/
        string name(){ return m_name; }
        /** Set name of item @param name @retval string*/
        string name(string name){ m_name = name; return m_name; }

        /** Get item description @retval string */
        string description(){ return m_desc; }
        /** Set item description @param desc @retval string */
        string description(string desc){ m_desc = desc; return m_desc; }

        /** Get item weight @retval int */
        int weight(){ return m_weight; }
        /** Set item weight @param weight @retval int */
        int weight(int weight){ m_weight = weight; return m_weight; }

    private:
        string m_name;
        string m_desc;
        int m_weight;
};

#endif /* ifndef ITEM_H */
