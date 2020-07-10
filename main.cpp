#include <iostream>
#include "Board.h"
#include "Game.h"

using namespace std;

void menu(){

}

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

    game.printGame();

    while(1){
        cout << "Please select the number: 1. place a stone  2. withdraw a stone  3. place a try-stone  4. withdraw a try-stone" << endl;
        cout << "5. print the board  6. replay game  7. replay try-game  8. refresh the board (Type number directly like 1, 2, or 3)" << endl;
        int modeNum;
        //;
        if(!(cin >> modeNum) || modeNum < 1 || modeNum > 8) {
            cout << "wrong number, please select again." << endl;
            continue;
        }

        switch (modeNum){
            case 1: //place a stone
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
                break;
            case 2: //withdraw a stone
                if (game.getMoveNum() > 0)
                    game.withdrawStone();
                else
                    cout << "No stone on the board. No stone to withdraw." << endl;
                break;
            case 3: //place a try-stone
                break;
            case 4: //withdraw a try-stone
                break;
            case 5: //print the board
                game.printGame();
                break;
            case 6: //replay the game
                game.replayStone();
                break;
            case 7: //replay all the try-stone game
                break;
            case 8: //refresh the board (clear all the try-stones)
                break;
            default:
                break;
        }
    }






    return 0;
}
