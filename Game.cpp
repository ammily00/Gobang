#include "Gomoku.h"
#include <iostream>
#include <string>
using namespace std;

Game::Game(){
    moveNUm = 0;
    tryStoneMoveNUm = 0;
}

Game::~Game(){

}

vector <char *> Game::splitString(char cmdString[10]){
/*
 * vector <char *> splVec;
 * if (cmdString == 'pass' || cmdString == 'Pass' || cmdString == 'PASS')
 *      splVec.push_back(nullptr);
 * else{
 *      char * spl;
 *      spl = strtok(cmdString, ":");
 *      while (spl != nullptr){
 *              splVec.push_back(spl);
 *              spl = strtok(nullptr, ":");
 *      }
 * return splIntVec;
 */

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

void Game::moveStone(char cmdString[10]){
/*
 * Move * moveAStone = new Move;
 * vector <char *> splVec = splitString(cmdString[10]);
 * if (splVec.at(0) != nullptr){
 *      moveAStone.seqNUm = stoi(splVec.at(0));
 *      if (splVec.at(1) == 'W' || splVec.at(1) == 'w')
 *              moveAStone.color = stoneWhite;
 *      else if (splVec.at(1) == 'B' || splVec.at(1) == 'b')
 *          moveAStone.color = stoneBlack;
 *      if (splVec.at(2) >= 'a' && splVec.at(2) <= 'z')
 *          moveAStone.x = splVec.at(2) - 97;
 *      else if (splVec.at(2) >= 'A' && splVec.at(2) <= 'Z')
 *          moveAStone.x = splVec.at(2) - 65;
 *      moveAStone.y = size - stoi(splVec.at(3));
 *      placeStone(moveAStone.x, moveAStone.y, moveAStone.color);
 *      moveNum++;
 *      moves.push_back(*moveAStone);
 *      withdraw_moves.push(*moveAStone);
 * }
 */
}

void Game::tryStone(char cmdString[10]){
/*
 * Move * moveATryStone = new Move;
 * vector <char *> splVec = splitString(cmdString[10]);
 * if (splVec.at(0) != nullptr){
 *      moveATryStone.seqNUm = stoi(splVec.at(0));
 *      if (splVec.at(1) == 'W' || splVec.at(1) == 'w')
 *          moveATryStone.color = stoneWhite;
 *      else if (splVec.at(1) == 'B' || splVec.at(1) == 'b')
 *          moveATryStone.color = stoneBlack;
 *      if (splVec.at(2) >= 'a' && splVec.at(2) <= 'z')
 *          moveATryStone.x = splVec.at(2) - 97;
 *      else if (splVec.at(2) >= 'A' && splVec.at(2) <= 'Z')
 *          moveATryStone.x = splVec.at(2) - 65;
 *      moveATryStone.y = size - stoi(splVec.at(3));
 *      placeStone(moveATryStone.x, moveATryStone.y, moveATryStone.color);
 *      tryStoneMoveNum++;
 *      moves.push_back(*moveATryStone);
 * }
 */
}

void Game::replay(){
/*
 * resetBoard();
 * In vector Move moves
 *      for each moves
 *          placeStone(moves.x, moves.y, moves.color);
 *          cout grid[][];
 *          sleep(1000);
 *      end
 *
 */
}

void Game::withdrawStone(){
/*
 * moveNum must > 0
 * Move recentStone = withdraw_moves.top();
 * remove(recentStone.x, recentStone.y);
 * withdraw_moves.pop();
 * moves.pop_back();
 * moveNum--;
 */
}

void Game::refresh(){
/*
 * resetBoard();
 * in vector Move moves
 *      for each moves
 *          placeStone(moves.x, moves.y, moves.color);
 *      end
 */
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