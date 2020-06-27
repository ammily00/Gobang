#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <string>

struct Move{
    /*
     * the coordinate, color and sequence number of the stone passed in by the user
     * in this form: sequence number:color:x_coordinatey_coordinate
     * ex: 1:B:H:5      200:W:A:10
     */
    char cmdString[10];

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

    Game();

    /*
     * delete all the stones and status, end the game
     */
    ~Game();

    /*
     * split the cmdString, return a string vector
     * vector.at(0) <- sequence number
     * vector.at(1) <- stone color
     * vector.at(2) <- x coordinate
     * vector.at(3) <- y coordinate
     */
    vector <char *> splitString();

    /*
     * check whether the state is correct (one black and one white)
     */
    bool checkState(int x, int y, stoneColor color);

    /*
     * new Stone()
     * Pass in the coordinate and color of the stone by the user input
     * Every time call move, increase the sequence number by 1
     * Call Stone:: getStone to check whether there is a stone in somewhere
     * If there are is no stone here, call Stone::placeStone to place the stone
     * Push this coordinate & stone color into the vector (for replay)
     * also store the stones in the array (for printBoard)
     */
    void moveStone(char cmdString[10]);

    /*
     * beyond the real game, guess where the players will place stones
     */
    void tryStone(char cmdString[10]);

    /*
     * After clearing the board, replay the game by sequence number
     */
    void replay();

    /*
     * stack pop (place stone: push)
     */
    void withdrawStone();

    /*
     * clear all the try-stones
     * implementation:
     * call Board::reset()
     * for each moves in Move, call placeStone
     */
    void refresh();

private:

    /*
     * move number default to be 0
     */
    int moveNum = 0;

    /*
     * store and display stones in sequence order
     */
    std::vector <Move> moves;

    /*
     * store stones in sequence order
     * used for withdrawStone, each time withdraw a stone, pop from the stack
     */
    std::stack <Move> withdraw_moves;
};

#endif /* GAME_H_ */
