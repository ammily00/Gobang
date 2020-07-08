#include "Gomoku.h"
#include <iostream>
#include <string>
using namespace std;

Game::Game(){
    moveNum = 0;
    tryStoneMoveNUm = 0;
}

Game::~Game(){
    moves.clear();
    tryStoneMoves.clear();
}

Move Game::splitString(char cmdString[4]){
    Move splitCmdString;
    if (cmdString == "Pass")
        splitCmdString = 0;
    else{
        //color is black or white
        if (cmdString[0] == "B")
            splitCmdString.color = stoneBlack;
        else if (cmdString[0] == "W")
            splitCmdString.color = stoneWhite;

        // y coordinate is from A to Z (convert back to 0~size-1)
        if (cmdString[1] >= 'A' && cmdString[1] <= 'Z')
            splitCmdString.y = cmdString[1] - 65;

        // convert x coordinate from size~1 to 0~size-1
        if (cmdString[3] == '\0')
            splitCmdString.x = size - cmdString[2] + 48;
        else if (cmdString[4] == '\0')
            splitCmdString.x = size - (cmdString[2] - 48) * 10 - (cmdString[3] - 48);
    }
    return splitCmdString;
}

Move Game::combineString(Move & moves){
    if (moves.cmdString == "Pass")
        moves.stoneRecord = moves.cmdString;
    else{
        if (seqNumber < 10){
            // sequence number
            moves.stoneRecord[0] = to_string(seqNumber);
            // ":"
            moves.stoneRecord[1] = ":";
            //color
            moves.stoneRecord[2] = moves.cmdString[0];
            // ":"
            moves.stoneRecord[3] = ":";
            // y coordinate
            moves.stoneRecord[4] = moves.cmdString[1];
            // ":"
            moves.stoneRecord[5] = ":";
            // x coordinate
            moves.stoneRecord[6] = moves.cmdString[2];
            moves.stoneRecord[7] = moves.cmdString[3];
        }
        else if (seqNum >= 10 && seqNum < 100){
            // sequence number
            moves.stoneRecord[0] = to_string(seqNumber / 10);
            moves.stoneRecord[1] = to_string(seqNumber % 10);
            // ":"
            moves.stoneRecord[2] = ":";
            //color
            moves.stoneRecord[3] = moves.cmdString[0];
            // ":"
            moves.stoneRecord[4] = ":";
            // y coordinate
            moves.stoneRecord[5] = moves.cmdString[1];
            // ":"
            moves.stoneRecord[6] = ":";
            // x coordinate
            moves.stoneRecord[7] = moves.cmdString[2];
            moves.stoneRecord[8] = moves.cmdString[3];
        }
        else if (seqNum >= 100 && seqNum < 1000){
            // sequence number
            moves.stoneRecord[0] = to_string(seqNumber / 100);
            moves.stoneRecord[1] = to_string(seqNumber % 100 / 10);
            moves.stoneRecord[2] = to_string(seqNumber % 10);
            // ":"
            moves.stoneRecord[3] = ":";
            //color
            moves.stoneRecord[4] = moves.cmdString[0];
            // ":"
            moves.stoneRecord[5] = ":";
            // y coordinate
            moves.stoneRecord[6] = moves.cmdString[1];
            // ":"
            moves.stoneRecord[7] = ":";
            // x coordinate
            moves.stoneRecord[8] = moves.cmdString[2];
            moves.stoneRecord[9] = moves.cmdString[3];
        }
    }
}

bool Game::validMove(Move & moves){
    if (moves.cmdString == "Pass")
        return true;
    if (moves.seqNum % 2 == 1 && moves.color == stoneBlack)
        return true;
    else if (moves.seqNum % 2 == 0 && moves.color == stoneWhite)
        return true;
    return false;
}

int Game::checkState(Move & moves){



    /*
 * if (grid[moves.x][moves.y] != NOSTONE)
 *      return -1;
 * if (moves.seqNum % 2 == 1 && moves.color == stoneBlack)
 *      return 0;
 * if (moves.seqNum % 2 == 0 && moves.color == stoneWhite)
 *      return 0;
 * if (moves.cmdString == 'pass' || moves.cmdString == 'Pass' || moves.cmdString == 'PASS')
 *      return 1;
 * return -1;
 */
}

void Game::moveStone(char cmdString[8]){
    Move moveAStone = splitString(cmdString);
    if (moveAStone!= 0){
        placeStone(moveAStone.x, moveAStone.y, moveAStone.color);
        moveAStone.seqNum = ++moveNum;
        moves.push_back(moveAStone);
    }
}

void Game::tryStone(char cmdString[8]){
    Move moveATryStone = splitString(cmdString);
    if (moveATryStone!= 0){
        placeStone(moveATryStone->x, moveATryStone->y, moveATryStone->color);
        moveATryStone->seqNum = ++tryStoneMoveNum;
        tryStoneMoves.push_back(moveATryStone);
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

    return blackWin;
    return whiteWin;

    return equalWin;
}





/*
void Gomoku::initChessBoard(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            chessboard[i][j] = '.';
        }
    }
}

int Gomoku::validPoint(const Point & point){
    if (point.x > 0 && point.x <= N && point.y > 0 && point.y <= N){ //within the chessboard
        if (chessboard[point.x][point.y] == '.') //do not have piece
            return 0; //valid
    }
    return -1; //invalid
}

void playChessInput(const Point & point, int player, char piece){
    printChessBoard();
    while(1){
        cout << "It is player" << player << "\'s turn" << endl; //player1 or player2
        cin >> point.x >> point.y;
        if (validPoint(point) == 0) //valid
            break;
        cout << "Invalid point, please input again!" << endl;
    }
    chesscoard[point.x][point.y] = piece; //'o' for player1 and 'x' for player2
}

void playChess(const Point & point, int player, char piece){
    playChessInput(point, player, piece);
}

void Gomoku::printChessBoard(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout << chessboard[i][j];
            if (j == N-1)
                cout << endl;
        }
    }
}

void Gomoku::judge(const Point & point, int player, char piece){

}

void Gomoku::play(){
    Point player1;
    Point player2;
    while(1){
        playChess(player1, 1, 'o');
        playChess(player2, 2, 'x');
        cout << "Want to start a new game? default yes, press n for no" << endl;
        char start_new;
        cin >> start_new;
        if (start_new == 'n')
            break;
    }

}
*/