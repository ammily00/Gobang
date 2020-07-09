#include "Game.h"
#include <iostream>
#include <string>
#include <unistd.h>
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
    if (cmdString[0] == 'P' && cmdString[1] == '\0' && cmdString[2] == '\0' && cmdString[3] == '\0')
        return true;
    //place a stone
    else{
        /* color is black or white
         * y coordinate is from A to Z
         * x coordinate is number from size to 1:
         * one-digit number, 0-9 for the units digit (0-9 for cmdString[2] and '\0' for cmdString[3]);
         * two-digit number, 1-9 for the tens digit and 0-9 for the units digit
         */
        if ((cmdString[0] == 'B' || cmdString[0] == 'W') &&
            (cmdString[1] >= 'A' && cmdString[1] <= 'Z') &&
            ((cmdString[2] >= 48 && cmdString[2] <= 57 && cmdString[3] == '\0') ||
             (cmdString[2] >= 49 && cmdString[2] <= 57 && cmdString[3] >= 48 && cmdString[3] <= 57)) &&
             cmdString[4] == '\0')
                return true;
    }
    return false;
}

Move * Game::splitString(char cmdString[4]){
    Move * splitCmdString = new Move;
    // P for pass, do not place a stone
    if (cmdString[0] == 'P' && cmdString[1] == '\0' && cmdString[2] == '\0' && cmdString[3] == '\0')
        splitCmdString = nullptr;
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

void Game::combineString(Move & moves){
    if (moves.cmdString[0] == 'P' && moves.cmdString[1] == '\0' &&
        moves.cmdString[2] == '\0' && moves.cmdString[3] == '\0')
        for (int i = 0; i < 4; i++)
            moves.stoneRecord[i] = moves.cmdString[i];
    else{
        if (moves.seqNum < 10){
            // sequence number
            // convert int to char
            moves.stoneRecord[0] = moves.seqNum + 48;
            // ":"
            moves.stoneRecord[1] = ':';
            //color
            moves.stoneRecord[2] = moves.cmdString[0];
            // ":"
            moves.stoneRecord[3] = ':';
            // y coordinate
            moves.stoneRecord[4] = moves.cmdString[1];
            // ":"
            moves.stoneRecord[5] = ':';
            // x coordinate
            moves.stoneRecord[6] = moves.cmdString[2];
            moves.stoneRecord[7] = moves.cmdString[3];
        }
        else if (moves.seqNum >= 10 && moves.seqNum < 100){
            // sequence number
            moves.stoneRecord[0] = moves.seqNum / 10 + 48;
            moves.stoneRecord[1] = moves.seqNum % 10 + 48;
            // ":"
            moves.stoneRecord[2] = ':';
            //color
            moves.stoneRecord[3] = moves.cmdString[0];
            // ":"
            moves.stoneRecord[4] = ':';
            // y coordinate
            moves.stoneRecord[5] = moves.cmdString[1];
            // ":"
            moves.stoneRecord[6] = ':';
            // x coordinate
            moves.stoneRecord[7] = moves.cmdString[2];
            moves.stoneRecord[8] = moves.cmdString[3];
        }
        else if (moves.seqNum >= 100 && moves.seqNum < 1000){
            // sequence number
            moves.stoneRecord[0] = moves.seqNum / 100 + 48;
            moves.stoneRecord[1] = moves.seqNum % 100 / 10 + 48;
            moves.stoneRecord[2] = moves.seqNum % 10 + 48;
            // ":"
            moves.stoneRecord[3] = ':';
            //color
            moves.stoneRecord[4] = moves.cmdString[0];
            // ":"
            moves.stoneRecord[5] = ':';
            // y coordinate
            moves.stoneRecord[6] = moves.cmdString[1];
            // ":"
            moves.stoneRecord[7] = ':';
            // x coordinate
            moves.stoneRecord[8] = moves.cmdString[2];
            moves.stoneRecord[9] = moves.cmdString[3];
        }
    }
}

//bool Game::validMove(Move & moves){
//    if (moves.cmdString[0] == 'P' && moves.cmdString[1] == '\0' &&
//        moves.cmdString[2] == '\0' && moves.cmdString[3] == '\0')
//        return true;
//    if (moves.seqNum % 2 == 1 && moves.color == stoneBlack)
//        return true;
//    else if (moves.seqNum % 2 == 0 && moves.color == stoneWhite)
//        return true;
//    return false;
//}

//int Game::checkState(Move & moves){
//    return 0;
//
//
//    /*
// * if (grid[moves.x][moves.y] != NOSTONE)
// *      return -1;
// * if (moves.seqNum % 2 == 1 && moves.color == stoneBlack)
// *      return 0;
// * if (moves.seqNum % 2 == 0 && moves.color == stoneWhite)
// *      return 0;
// * if (moves.cmdString == 'pass' || moves.cmdString == 'Pass' || moves.cmdString == 'PASS')
// *      return 1;
// * return -1;
// */
//}

void Game::moveStone(char cmdString[4]){
    Move * moveAStone = splitString(cmdString);
    if (moveAStone!= 0){
        board.placeStone(moveAStone->x, moveAStone->y, moveAStone->color);
        moveAStone->seqNum = ++moveNum;
        moves.push_back(*moveAStone);
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
    resetBoard();
    for (vector<Move>::iterator it = moves.begin(); it != moves.end(); it++){
        placeStone(moves.x, moves.y, moves.color);
        printBoard();
        sleep(1000);
    }
}

void Game::replayTryStone(){
    refresh();
    for (vector<Move>::iterator it = tryStoneMoves.begin(); it != tryStoneMoves.end(); it++){
        placeStone(tryStoneMoves.x, tryStoneMoves.y, tryStoneMoves.color);
        printBoard();
        sleep(1000);
    }
}

void Game::withdrawStone(){
    Move recentStone = moves.back();
    remove(recentStone.x, recentStone.y);
    moves.pop_back();
    moveNum--;
}

void Game::withdrawTryStone(){
    Move recentTryStone = tryStoneMoves.back();
    remove(recentTryStone.x, recentTryStone.y);
    tryStoneMoves.pop_back();
    tryStoneMoveNum--;
}

void Game::refresh(){
    resetBoard();
    for (vector<Move>::iterator it = moves.begin(); it != moves.end(); it++){
        placeStone(moves.x, moves.y, moves.color);
    }
    printBoard();
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