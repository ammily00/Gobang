#ifndef GAME_H_
#define GAME_H_

#include <vector>

class Game {
public:
    /*
     * start the game
     * sequence number default to be 0
     * initialize the array
     */
    Game();

    /*
     * end the game
     */
    ~Game();

    /*
     * Pass in the coordinate and color of the stone by the user input
     * Every time call move, increase the sequence number by 1
     * Call Stone:: getStone to check whether there is a stone in somewhere
     * If there are is no stone here, call Stone::placeStone to place the stone
     * Push this coordinate & stone color into the vector (for replay)
     * also store the stones in the array
     */
    void move(int x, int y, stoneColor color);
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
