#include "Game.h"
#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;

Game::Game(int size): board(size){
    this->size = size;
    moveNum = 0;
    tryStoneMoveNum = 0;
}

Game::~Game(){
    moves.clear();
    tryStoneMoves.clear();
}

bool Game::validCmdString(char cmdString[4]){
    // P for pass (do not place a stone)
    if ((cmdString[0] == 'B' || cmdString[0] == 'W') &&
            cmdString[1] == 'P' && cmdString[2] == '\0' && cmdString[3] == '\0'){
        //cout << "here!" << endl;
        return true;
    }

    //place a stone
    else{
        //extract x coordinate
        char c[2];
        c[0] = cmdString[2];
        c[1] = cmdString[3];
        string s = "";
        s += c[0];
        s += c[1];

        /* color is black or white
         * y coordinate is from A to Z
         * x coordinate is number from size to 1:
         * one-digit number, 1-9 for the units digit (1-9 for cmdString[2] and '\0' for cmdString[3]);
         * two-digit number, 1-9 for the tens digit and 0-9 for the units digit
         * also the range should be within the size
         * make sure black stone first and white stone later
         * As moveNum is increased by one and given to seqNum only if a "moveStone" operation,
         * so the moveNum used to judge is the seqNum for the most previous stone.
         */
        if ((cmdString[0] == 'B' || cmdString[0] == 'W') &&
                (cmdString[1] >= 'A' && cmdString[1] <= 'Z') &&
                (cmdString[2] >= 49 && cmdString[2] <= 57) &&
                (cmdString[3] == '\0' || (cmdString[3] >= 48 && cmdString[3] <= 57)) &&
                ((moveNum % 2 == 0 && cmdString[0] == 'B') || (moveNum % 2 == 1 && cmdString[0] == 'W'))){
            if (size < 10 && cmdString[1] <= 'A' + size - 1 && cmdString[3] == '\0')
                return true;
            else if (size >= 10 && stoi(s) <= size && cmdString[1] <= 'A' + size - 1)
                return true;
        }
    }
    return false;
}

Move * Game::splitString(char cmdString[4]){
    Move * splitCmdString = new Move;
    strcpy(splitCmdString->cmdString, cmdString);
    // P for pass, do not place a stone
    if ((cmdString[0] == 'B' || cmdString[0] == 'W') &&
            cmdString[1] == 'P' && cmdString[2] == '\0' && cmdString[3] == '\0'){
        if (cmdString[0] == 'B')
            splitCmdString->color = stoneBlack;
        else if (cmdString[0] == 'W')
            splitCmdString->color = stoneWhite;
    }

    // place a stone
    else{
        //color is black or white
        if (cmdString[0] == 'B')
            splitCmdString->color = stoneBlack;
        else if (cmdString[0] == 'W')
            splitCmdString->color = stoneWhite;

        // y coordinate is from A to Z (convert back to 0~size-1)
        if (cmdString[1] >= 'A' && cmdString[1] <= 'Z')
            splitCmdString->y = cmdString[1] - 65;

        // convert x coordinate from size~1 to 0~size-1
        // one-digit number, 0-9 for the units digit (0-9 for cmdString[2] and '\0' for cmdString[3])
        if (cmdString[2] >= 48 && cmdString[2] <= 57 && cmdString[3] == '\0')
            splitCmdString->x = size - cmdString[2] + 48;
        // two-digit number, 1-9 for the tens digit (cmdString[2]) and 0-9 for the units digit (cmdString[3])
        else if (cmdString[2] >= 49 && cmdString[2] <= 57 && cmdString[3] >= 48 && cmdString[3] <= 57)
            splitCmdString->x = size - (cmdString[2] - 48) * 10 - (cmdString[3] - 48);
    }
    return splitCmdString;
}

void Game::displayRecord(){
    for (vector<Move>::iterator it = moves.begin(); it != moves.end(); it++){
        if ((it->cmdString[0] == 'B' || it->cmdString[0] == 'W') &&
                it->cmdString[1] == 'P' && it->cmdString[2] == '\0' && it->cmdString[3] == '\0'){
            cout << it->seqNum << ":" << it->cmdString[0] << ":" << it->cmdString[1] << endl;
        }
        else{
            cout << it->seqNum << ":" << it->cmdString[0] << ":" << it->cmdString[1] << ":"
                 << it->cmdString[2] << it->cmdString[3] << endl;
        }
    }
}

void Game::moveStone(char cmdString[4]){
    Move * moveAStone = splitString(cmdString);
    if (moveAStone->x == -1 && moveAStone->y == -1){ //no stone will be placed (instead, choose to pass)
        moveAStone->seqNum = ++moveNum;
        moves.push_back(*moveAStone);
    }
    else{ // a stone will be placed instead of passing
        Stone * intersection = board.getStone(moveAStone->x, moveAStone->y);
        // no stone in this intersection
        if (intersection == nullptr) {
            board.placeStone(moveAStone->x, moveAStone->y, moveAStone->color);
            moveAStone->seqNum = ++moveNum;
            moves.push_back(*moveAStone);

            // check victory
            if (checkVictory(moveAStone->x, moveAStone->y, moveAStone->color) == moveAStone->color){
                cout << moveAStone->color << "wins." << endl;
                status = GameEnd;
            }
        }
        else{
            if (intersection->color == stoneBlack)
                cout << "A black stone has been placed at" << cmdString[1] << cmdString[2] << cmdString[3] << endl;
            else if (intersection->color == stoneWhite)
                cout << "A white stone has been placed at" << cmdString[1] << cmdString[2] << cmdString[3] << endl;
        }
    }
}

int Game::getGameStatus(){
    return status;
}

void Game::tryStone(char cmdString[4]){
    Move * moveATryStone = splitString(cmdString);
    if (moveATryStone!= 0){
        board.placeStone(moveATryStone->x, moveATryStone->y, moveATryStone->color);
        moveATryStone->seqNum = ++tryStoneMoveNum;
        tryStoneMoves.push_back(*moveATryStone);
    }
}

void Game::replayStone(){
    board.resetBoard();
    board.printBoard();
    for (vector<Move>::iterator it = moves.begin(); it != moves.end(); it++){
        if (it->x != -1 && it->y != -1) //make sure it is a real stone instead of passing
            board.placeStone(it->x, it->y, it->color);

        time_t start;
        start = time(0);
        int n = 1; //1 second
        while(1){
            if(time(0) - start == n) {//print every n second(s)
                board.printBoard();
                //cout << it->x << it->y << it->color << endl;
                start = start + n;
                break;
            }
        }
    }
    cout << endl;
}

void Game::replayTryStone(){
    refresh();
    for (vector<Move>::iterator it = tryStoneMoves.begin(); it != tryStoneMoves.end(); it++){
        if (it->x != -1 && it->y != -1) //make sure it is a real stone instead of passing
            board.placeStone(it->x, it->y, it->color);

        time_t start;
        start = time(0);
        int n = 1; //1 second
        while(1){
            if(time(0) - start == n) {//print every n second(s)
                board.printBoard();
                //cout << it->x << it->y << it->color << endl;
                start = start + n;
                break;
            }
        }
    }
    cout << endl;
}

void Game::withdrawStone(){
    Move * recentStone = &(moves.back());
    if (recentStone->x != -1 && recentStone->y != -1)
        board.removeStone(recentStone->x, recentStone->y);
    moves.pop_back();
    moveNum--;
}

void Game::withdrawTryStone(){
    Move * recentTryStone = &(tryStoneMoves.back());
    board.removeStone(recentTryStone->x, recentTryStone->y);
    tryStoneMoves.pop_back();
    tryStoneMoveNum--;
}

void Game::refresh(){
    board.resetBoard();
    for (vector<Move>::iterator it = moves.begin(); it != moves.end(); it++){
        board.placeStone(it->x, it->y, it->color);
    }
    board.printBoard();
}

int Game::checkVictory(int x, int y, stoneColor color){
    // check whether there are five sequential stones in the same color as the stone passed in
    bool win = false;
    // true means that the stone passed in is in the five sequential stones in this row/column/diagonal
    bool found = false;

    // row
    for (int j = 0; j < size; j++){
        if (j < size - 4) {
            if (board.grid[x][j].color == color && board.grid[x][j+1].color == color &&
                board.grid[x][j+2].color == color && board.grid[x][j+3].color == color &&
                board.grid[x][j+4].color == color)
                win = true;
            if (y == j || y == j+1 || y == j+2 || y == j+3 || y == j+4)
                found = true;
            if (win == true && found == true){
                win = false;
                found = false;
                return color;
            }
            else{
                win = false;
                found = false;
            }
        }
    }

    // column
    for (int i = 0; i < size; i++){
        if (i < size - 4) {
            if (board.grid[x][i].color == color && board.grid[x][i+1].color == color &&
                board.grid[x][i+2].color == color && board.grid[x][i+3].color == color &&
                board.grid[x][i+4].color == color)
                win = true;
            if (y == i || y == i+1 || y == i+2 || y == i+3 || y == i+4)
                found = true;
            if (win == true && found == true){
                win = false;
                found = false;
                return color;
            }
            else{
                win = false;
                found = false;
            }
        }
    }

    // diagonal (left top to right bottom)


    return -1;
//    return blackWin;
//    return whiteWin;
//
//    return equalWin;
}

void Game::printGame(){
    board.printBoard();
}

int Game::getMoveNum(){
    return moveNum;
}