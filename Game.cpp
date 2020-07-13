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
            else if (size >= 10 && stoi(s) <= size)
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

void Game::combineString(Move & move){
//    cout << "prrint cmdString" << endl;
//    for (int i = 0; i < 4; i++){
//        cout << i << move.cmdString[i];
//        if (i == 3)
//            cout << endl;
//        else
//            cout << "\t";
//    }

    if ((move.cmdString[0] == 'B' || move.cmdString[0] == 'W') &&
        move.cmdString[1] == 'P' && move.cmdString[2] == '\0' && move.cmdString[3] == '\0'){
        // sequence number
        // convert int to char
        move.stoneRecord[0] = move.seqNum + 48;
        // ":"
        move.stoneRecord[1] = ':';
        //color
        move.stoneRecord[2] = move.cmdString[0];
        // ":"
        move.stoneRecord[3] = ':';
        // "P"
        move.stoneRecord[4] = 'P';
    }
    else{
        if (move.seqNum < 10){
            // sequence number
            // convert int to char
            move.stoneRecord[0] = move.seqNum + 48;
            // ":"
            move.stoneRecord[1] = ':';
            //color
            move.stoneRecord[2] = move.cmdString[0];
            // ":"
            move.stoneRecord[3] = ':';
            // y coordinate
            move.stoneRecord[4] = move.cmdString[1];
            // ":"
            move.stoneRecord[5] = ':';
            // x coordinate
            move.stoneRecord[6] = move.cmdString[2];
            move.stoneRecord[7] = move.cmdString[3];
        }
        else if (move.seqNum >= 10 && move.seqNum < 100){
            // sequence number
            move.stoneRecord[0] = move.seqNum / 10 + 48;
            move.stoneRecord[1] = move.seqNum % 10 + 48;
            // ":"
            move.stoneRecord[2] = ':';
            //color
            move.stoneRecord[3] = move.cmdString[0];
            // ":"
            move.stoneRecord[4] = ':';
            // y coordinate
            move.stoneRecord[5] = move.cmdString[1];
            // ":"
            move.stoneRecord[6] = ':';
            // x coordinate
            move.stoneRecord[7] = move.cmdString[2];
            move.stoneRecord[8] = move.cmdString[3];
        }
        else if (move.seqNum >= 100 && move.seqNum < 1000){
            // sequence number
            move.stoneRecord[0] = move.seqNum / 100 + 48;
            move.stoneRecord[1] = move.seqNum % 100 / 10 + 48;
            move.stoneRecord[2] = move.seqNum % 10 + 48;
            // ":"
            move.stoneRecord[3] = ':';
            //color
            move.stoneRecord[4] = move.cmdString[0];
            // ":"
            move.stoneRecord[5] = ':';
            // y coordinate
            move.stoneRecord[6] = move.cmdString[1];
            // ":"
            move.stoneRecord[7] = ':';
            // x coordinate
            move.stoneRecord[8] = move.cmdString[2];
            move.stoneRecord[9] = move.cmdString[3];
        }
    }
}

void Game::displayRecord(){
    for (vector<Move>::iterator it = moves.begin(); it != moves.end(); it++){
//        for (int i = 0; i < 4; i ++)
//            cout << it->cmdString[i] << endl;
        combineString(*it);
        cout << it->stoneRecord << endl;
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
        }
        else{
            if (intersection->color == stoneBlack)
                cout << "A black stone has been placed at" << cmdString[1] << cmdString[2] << cmdString[3] << endl;
            else if (intersection->color == stoneWhite)
                cout << "A white stone has been placed at" << cmdString[1] << cmdString[2] << cmdString[3] << endl;
        }
    }
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
    //cout << "~~~" << recentStone->x << recentStone->y << recentStone->color << endl;
    board.removeStone(recentStone->x, recentStone->y);
    //cout << "..." << recentStone->x << recentStone->y << recentStone->color << endl;
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

int Game::checkVictory(){
    return 0;
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