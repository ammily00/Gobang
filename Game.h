#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <string>

typedef enum {
    gameStart,
    gameProcess,
    GameEnd
} gameStatus;

typedef enum {
    blackWin,
    whiteWin
} winner;

struct Move {
    /*
     * the coordinate, color and sequence number of the stone passed in by the user
     * in this form: color:x_coordinate:y_coordinate
     * ex: B:H:5      W:A:10
     */
    char cmdString[8];

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
     * or to say: destroy the Game object including all associates
     */
    ~Game();

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
    void moveStone(char cmdString[8]);

    /*
     * beyond the real game, guess where the players will place stones
     */
    void tryStone(char cmdString[8]);

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
    int moveNum;

    /*
     * move number of tryStone default to be 0
     */
    int tryStoneMoveNum;

    /*
     * status of the game
     * gameStart: game starts (the initial status, before the first stone is placed on the board)
     * gameProcess: game processes (from the first stone to the result of the game)
     * gameEnd: game ends, no more operations
     */
    gameStatus status;
    
    /*
     * split the cmdString, return a Move object
     * vector.at(0) <- stone color
     * vector.at(1) <- x coordinate
     * vector.at(2) <- y coordinate
     */
    Move splitString(char cmdString[8]);

    /*
     * store and display stones in sequence order
     */
    std::vector <Move> moves;

    /*
     * store and display tryStones in sequence order
     */
    std::vector <Move> tryStoneMoves;

    /*
     * store stones in sequence order
     * used for withdrawStone, each time withdraw a stone, pop from the stack
     */
    //std::stack <Move> withdraw_moves;
};

#endif /* GAME_H_ */
