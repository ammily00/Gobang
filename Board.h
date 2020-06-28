#ifndef BOARD_H_
#define BOARD_H_
#define NOSTONE 999
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
    Stone * getStone(int x, int y);

    /*
     * place a black/white stone to the specific coordinate
     * if there is no stone in the intersection, first remove it then place stone
     * inside, new Stone
     */
    void placeStone(int x, int y, colorStone color);

    /*
     * remove a stone at the user specific location
     */
    void removeStone(int x, int y);

    /*
     * reset the board to the genuine state
     */
    void resetBoard();


private:

    /*
     * the size (size*size) of the board
     */
    int size;

    /*
     * store stones in a two dimensional array
     */
    int grid[size][size];
};


#endif /* BOARD_H_ */
