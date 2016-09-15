#include "floor_tile.h"

/**
 * Construct a FloorTile with the given X and Y coordinates.
 * @param[in] x
 * @param[in] y
 */
FloorTile::FloorTile(int x, int y){
    m_symbol = '#';
    m_x = x;
    m_y = y;
    m_depth = 100;
}

/**
 * Construct a FloorTile with the given X and Y coordinates, and the given symbol.
 * @param[in] x
 * @param[in] y
 * @param[in] symbol The symbol to display
 */
FloorTile::FloorTile(int x, int y, char symbol){
    m_symbol = symbol;
    m_x = x;
    m_y = y;
    m_depth = 100;
}

/**
 * Check if the FloorTile is visible.
 * @retval bool
 */
bool FloorTile::visible(){
    // TODO: implement line-of-sight
    return true;
}

/**
 * Check if the FloorTile location is known
 * @retval bool
 */
bool FloorTile::known(){
    // TODO: implement player memory
    return true;
}

/**
 * Check if movement through the FloorTile is prohibited
 * @retval bool
 */
bool FloorTile::blocksMovement(){
    /* always traversable */
    return false;
}

/**
 * Move the FloorTile to the given X and Y coordinates.
 * @param x
 * @param y
 * @retval bool `true` if the move succeeded, `false` otherwise.
 */
bool FloorTile::move(int x, int y){
    /* cannot move */
    return false;
}
