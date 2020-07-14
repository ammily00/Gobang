#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <string>
#include <ctime>
#include "Board.h"
#include "Move.h"

typedef enum {
    GameStart,
    GameEnd
} gameStatus;

typedef enum {
    blackWin,
    whiteWin,
    equalWin
} winner;


class Game {
public:

    Game(int size);

    /*
     * delete all the stones and status, end the game
     * or to say: destroy the Game object including all associates
     */
    ~Game();

//    /*
//     * check whether the state is correct (one black and one white)
//     */
//    bool checkState(int x, int y, stoneColor color);

    /*
     * check if the input command string is valid
     * two situations
     * 1. P for pass (no stone is placed)
     * 2. place a stone
     * every digit has its own meaning and requirements
     */
    bool validCmdString(char cmdString[4]);

    /*
     * new Stone()
     * Pass in the coordinate and color of the stone by the user input
     * Every time call move, increase the sequence number by 1
     * Call Stone:: getStone to check whether there is a stone in somewhere
     * If there is no stone here, call Stone::placeStone to place the stone
     * Push this coordinate & stone color into the vector (for replay)
     * also store the stones in the array (for printBoard)
     */
    void moveStone(char cmdString[4]);

    /*
     * beyond the real game, guess where the players will place stones
     */
    void tryStone(char cmdString[4]);

    /*
     * After clearing the board, replay the game by sequence number
     */
    void replayStone();

    /*
     * After moving all the tryStones and keep the original stones, replay the tryStones be sequence number
     */
    void replayTryStone();

    /*
     * Every time call this function, withdraw the most recent stone
     */
    void withdrawStone();

    /*
     * Every time call this function, withdraw the most recent trystone
     */
    void withdrawTryStone();

    /*
     * clear all the try-stones
     * implementation:
     * call Board::reset()
     * for each moves in Move, call placeStone
     */
    void refresh();

    /*
     * rules to judge the winner
     */
    int checkVictory();

    /*
     * print the board and the stones
     */
    void printGame();

    int getMoveNum();

    void displayRecord();

    int getGameStatus();

private:
    /*
     * use Board object
     */
    Board board;

    int size;

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
    gameStatus status = GameStart;

    /*
     * split the cmdString
     * return a nullptr if no stone is placed (P for pass)
     * return a Move object pointer if a stone is placed
     */
    Move * splitString(char cmdString[4]);

    int checkVictory(int x, int y, stoneColor color);

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
