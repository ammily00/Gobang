#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(int size){
/*
 * size = 15; //could be changed if needed
 * resetBoard();
 */


}

Board::~Board(){

}

void Board::printBoard(){
/*
 * In grid[size][size]
 *      for i in size
 *          for j in size
 *              cout << grid[i][j] << endl;
 *          end
 *      end
 */
}

Stone * Board::getStone(int x, int y){
/*
 * if (grid[x][y] == NOSTONE)
 *      return nullptr;
 * else{
 *      Stone * stone;
 *      stone.x = x;
 *      stone.y = y;
 *      stone.color = grid[x][y];
 *      return stone;
 * }
 */
}

void Board::placeStone(int x, int y, stoneColor color){
/*
 * grid[x][y] = color;
 */
}

void Board::removeStone(int x, int y){
/*
 * grid[x][y] = NOSTONE;
 */
}

void Board::resetBoard(){
/*
 * In grid[size][size]
 *      for i in size
 *          for j in size
 *              grid[i][j] = NOSTONE;
 *          end
 *      end
 */
}