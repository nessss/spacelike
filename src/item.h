#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "onscreen_element.h"
#include "named_element.h"

using namespace std;

class Item : public OnscreenElement, public NamedElement{
    public:

        enum Group : int
        {
            None = 0,
            Weapon,
            Equipment,
            Tool,
            Consumable,
            Craftable,
            Quest
        };

        Item(   string name = "",
                string description = "",
                Item::Group group = Item::Group::None,
                int weight = 0,
                int value = 0 );

        string name(){ return m_name; }
        string name( string name ){ m_name = name; return m_name; }

        string description(){ return m_description; }
        string description( string desc ){ m_description = desc; return m_description; }

        Group group(){ return m_group; }
        Group group( Group newGroup ){ m_group = newGroup; return m_group; }

        int weight(){ return m_weight; }
        int weight( int weight ){ m_weight = weight; return m_weight; }

        int value(){ return m_value; }
        int value( int value ){ m_value = value; return m_value; }

        bool visible();
        bool known();
        bool move(int x, int y);

    private:
        string m_name;
        string m_description;
        Group m_group;
        int m_weight;
        int m_value;
};

#endif /* ifndef ITEM_H */
