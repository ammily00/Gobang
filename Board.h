#ifndef BOARD_H_
#define BOARD_H_
#include "Stone.h"

class Board {
public:
    /*
     * Constructor: take parameter annotation
     * initialize the board
     */
    Board(int size);

    ~Board();

    /*
     * output the board in a displayable way into the console
     */
    void printBoard();

    /*
     * return null pointer if the intersection is empty (so the new stone can be placed)
     * return the pointer of Stone means there is already a stone on the intersection (so the new stone can not be placed)
     */
    bool getStone(int x, int y);

    /*
     * place a black/white stone to the specific coordinate
     * if there is no stone in the intersection, first remove it then place stone
     * inside, new Stone
     */
    void placeStone(int x, int y, stoneColor color);

    /*
     * remove a stone at the user specific location
     */
    void removeStone(int x, int y);

    /*
     * reset the board to the genuine state
     */
    void resetBoard();

    /*
     * class Game can access public members of class Board
     */
    friend class Game;


private:

    /*
     * the size (size*size) of the board
     */
    int size;

    /*
     * store stones in a two dimensional array
     */
    Stone **grid;
};


#endif /* BOARD_H_ */
