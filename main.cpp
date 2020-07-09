#include <iostream>
#include "Board.h"
#include "Game.h"

using namespace std;


int main(){
//    Board board(5);
//    board.placeStone(2, 3, stoneBlack);
//    board.placeStone(1, 1, stoneWhite);
//    board.placeStone(4, 2, stoneBlack);
//    board.placeStone(3, 4, stoneWhite);
//    board.printBoard();
//    board.removeStone(4, 2);
//    board.printBoard();
//    cout << board.getStone(1, 1) << endl;
//    cout << board.getStone(3, 3) << endl;
//    return 0;

    cout << "Welcome to the Gobang Game!" << endl << endl;
    cout << "Please choose the size of the board, size must be in the range [6, 31]" << endl;
    int boardSize;
    cin >> boardSize;
    cout << endl;
    while (boardSize < 6 || boardSize > 31){
        cout << "\nwrong number, please input again" << endl;
        cin >> boardSize;
        cout << endl;
        if (boardSize >= 6 && boardSize <= 31)
            break;
    }

    Game game(boardSize);

    cout << "Please enter the intersection where you want to place the stone." << endl;
    cout << "Stones must be in this format: "
            "color(B for black, W for white)y coordinate(starting from A to A + size - 1)x coordinate(size~1)" << endl;
    cout << "Or you can choose to skip by pressing P for pass" << endl;
    cout << "For example:  BA1   WB10   P   P" << endl;
    char commandString[4];
    cin >> commandString;
    cout << endl;
    while (!game.validCmdString(commandString)){
        cout << "\nwrong string, please input again" << endl;
        cin >> commandString;
        cout << endl;
        if (game.validCmdString(commandString))
            break;
    }
    game.moveStone(commandString);
    game.printGame();

    return 0;
}
