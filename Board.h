#ifndef BOARD_H_
#define BOARD_H_



class Board {
public:
    /*
     * Constructor: take parameter annotation
     */
    Board(int size);

    ~Board();

    /*
     * output the board in a displayable way
     */
    void printBoard();

    /*
     * return null pointer if the intersection is empty and the new stone can be placed
     * return the pointer of Stone means there is already a stone on the intersection, the new stone can not be placed
     */
    Stone * getStone(int x, int y);

    /*
     * place a black/white stone to somewhere
     * if there is no stone in the intersection, first remove it then place stone
     */
    void placeStone(Stone & stone);

    /*
     * remove a stone
     */
    void removeStone(int x, int y);

    /*
     * clear the board and prepare for the new game to start (clearing everything)
     */
    void resetBoard();


private:

    /*
     * the size (size*size) of the board
     */
    int size;
};


#endif /* BOARD_H_ */
