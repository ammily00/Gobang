#ifndef GAME_H_
#define GAME_H_

#include <vector>

struct Move{
    /*
     * the coordinate, color and sequence number of the stone passed in by the user
     * in this form: sequence number:color:x coordinate:ycoordinate
     * ex: 1:B:H:5      200:W:A:10
     */
    char cmdSting[12];

    /*
     * sequence number
     */
    int seqNum;

    /*
     * x coordinate
     */
    int x;

    /*
     * y coordinate
     */
    int y;

    /*
     * stone color
     */
    stoneColor color;
};

class Game {
public:
    /*
     *
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
    void moveStone(cmdString);

    void tryStone();

    /*
     * After clearing the board, replay the game by sequence number
     */
    void replay();

    /*
     * stack pop (not real sequence) (place stone: push)
     * clear all the try-stones
     */
    void refresh();

private:

    /*
     * move number default to be 0
     */
    int moveNum;

    /*
     * store and display stones in sequence order
     */
    std::vector<Move> moves;
};

#endif /* GAME_H_ */
