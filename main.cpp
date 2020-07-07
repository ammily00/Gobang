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
    cout << board.getStone(1, 1) << endl;
    cout << board.getStone(3, 3) << endl;
    return 0;
}
