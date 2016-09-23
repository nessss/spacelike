/**
 * An openable, closable door.
 */

#ifndef DOOR_H
#define DOOR_H

#include "tile.h"

class Door : public Tile{
    public:
        Door(int x, int y, char openSymbol, char closedSymbol);
        Door(int x, int y) : Door(x, y, '+', '-') {}
        Door() : Door(0, 0, '+', '-') {}

        bool Open();
        bool Close();
        bool Toggle();

        virtual char getSymbol() override;
        virtual bool blocksMovement() const override;

    private:
        char m_openSymbol;
        char m_closedSymbol;
        bool m_open;
};

#endif /* DOOR_H */
