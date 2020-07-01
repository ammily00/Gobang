#include <iostream>
#include "Board.h"


using namespace std;


int main(){
    Board board(5);
    board.placeStone(2, 3, stoneBlack);
    board.placeStone(1, 1, stoneWhite);
    board.placeStone(4, 2, stoneBlack);
    board.placeStone(3, 4, stoneWhite);
    board.printBoard();
    board.removeStone(4, 2);
    board.printBoard();
    cout << (board.getStone(1, 1))->x << " "
         << (board.getStone(1, 1))->y << " "
         << (board.getStone(1, 1))->color << endl;
    return 0;
}
