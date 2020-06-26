#ifndef BOARD_H_
#define BOARD_H_



class Board {
public:
    /*
     * set the size (size*size) of the board
     */
    Board(int size);

    ~Board();

    /*
     * show all the stones on the board
     */
    void printBoard();

    /*
     * return value true means the intersection is empty and the new stone can be placed
     * false means there is already a stone on the intersection, the new stone can not be placed
     */
    bool getStone(int x, int y); //every time places a stone, update the board

    /*
     * place a black/white stone to somewhere
     * implement this function after checking the return value of getStone
     */
    void placeStone(int x, int y, stoneColor color);

    /*
     * remove the most previous stone (if someone regrets a stone)
     */
    void removeStone(int x, int y, stoneColor color);

    /*
     * After clearing the board, replay the game by sequence number
     */
    void replay();

    /*
     * just clear the performance, remain the contents
     */
    void clearBoard();

    /*
     * clear the board and prepare for the new game to start (clearing everything)
     */
    void resetBoard();


private:
    vector<Stone> stone; // all the stones placed

    /*
     * the size (size*size) of the board
     */
    int size;

    friend class Game;

};


#endif /* BOARD_H_ */
