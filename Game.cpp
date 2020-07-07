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

Move * Game::splitString(char cmdString[8]){
    vector <char *> splVec;
    if (cmdString == "Pass")
        splVec.push_back(nullptr);
    else {
        char *spl;
        spl = strtok(cmdString, ":");
        while (spl != nullptr) {
            splVec.push_back(spl);
            spl = strtok(nullptr, ":");
        }
    }
    
    Move * movefromSplit = new Move;
    if (splVec.at(0) != nullptr) {
        if (splVec.at(0) == "W")
            movefromSplit->color = stoneWhite;
        else if (splVec.at(0) == "B")
            movefromSplit->color = stoneBlack;
        if (splVec.at(1).at(0) >= 'A' && splVec.at(1).at(0) <= 'Z')
            movefromSplit->x = splVec.at(1).at(0) - 65;
        movefromSplit->y = size - stoi(splVec.at(2));
    }
    else{
        movefromSplit = nullptr;
    }
    return movefromSplit;
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
    Move * moveAStone = splitString(cmdString);
    if (moveAStone!= nullptr){
        placeStone(moveAStone->x, moveAStone->y, moveAStone->color);
        moveAStone->seqNum = ++moveNum;
        moves.push_back(*moveAStone);
    }
}

void Game::tryStone(char cmdString[8]){
    Move * moveATryStone = splitString(cmdString);
    if (moveATryStone!= nullptr){
        placeStone(moveATryStone->x, moveATryStone->y, moveATryStone->color);
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