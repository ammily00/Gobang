#ifndef GAME_H_
#define GAME_H_

#include <vector>

class Game {
public:
    /*
     * sequence number default to be 0
     * initialize the array
     */
    Game();

    /*
     * delete all the stones and status, end the game
     */
    ~Game();

    /*
     * check whether the state is correct (one black and one white)
     */
    bool checkState();

    /*
     * new Stone()
     * Pass in the coordinate and color of the stone by the user input
     * Every time call move, increase the sequence number by 1
     * Call Stone:: getStone to check whether there is a stone in somewhere
     * If there are is no stone here, call Stone::placeStone to place the stone
     * Push this coordinate & stone color into the vector (for replay)
     * also store the stones in the array (for printBoard)
     */
    void move(int x, int y, stoneColor color);

    /*
     * After clearing the board, replay the game by sequence number
     */
    void replay();

    /*
     * stack pop (not real sequence) (place stone: push)
     */
    void refreshBoard();
};

private:

    /*
     * sequence number
     */
    int seqNum;

    /*
     * store and display stones in sequence order
     */
    std::vector<Stone> stoneSeq;

    /*
     * store stones in a two dimensional array, the value is its color
     */
    int Stone[size][size];


#endif /* GAME_H_ */
