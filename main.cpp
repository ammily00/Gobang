#include <iostream>
#include "Board.h"
#include "Game.h"

using namespace std;

bool check_number(string str) {
    for (unsigned int i = 0; i < str.length(); i++){
        if (isdigit(str[i]) == false)
            return false;
    }
    return true;
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
//    cout << board.getStone(2, 3)->x << board.getStone(2, 3)->y << board.getStone(2, 3)->color << endl;
//    //cout << board.getStone(3, 3) << endl;
//    return 0;


    cout << "Welcome to the Gobang Game!" << endl << endl;
    cout << "Please choose the size of the board, size must be in the range [6, 31] (usually an odd number)" << endl;
    //make sure boardSize is an interger in range [6, 31].
    string boardSize;
    cin >> boardSize;
    cout << endl;
    while (!check_number(boardSize) || stoi(boardSize) < 6 || stoi(boardSize) > 31){
        cout << "\nwrong number, please input again" << endl;
        cin >> boardSize;
        cout << endl;
        if (check_number(boardSize) && stoi(boardSize) >= 6 && stoi(boardSize) <= 31)
            break;
    }

    Game game(stoi(boardSize));

    game.printGame();

    while(1){
        cout << "Please select the number: 1. place a stone  2. withdraw a stone  "
                "3. place a try-stone  4. withdraw a try-stone" << endl;
        cout << "5. print the board  6. replay game  7. replay try-game  "
                "8. refresh the board (Type number directly like 1, 2, or 3)" << endl;
        cout << "9. display stone record " << endl;
        // make sure modeNum is an integer in range [1, 9]
        string modeNum;
        cin >> modeNum;
        if(!check_number(modeNum) || stoi(modeNum) < 1 || stoi(modeNum) > 9) {
            cout << "wrong number, please select again." << endl;
            continue;
        }

        switch (stoi(modeNum)){
            case 1: //place a stone
                cout << "Please enter the intersection where you want to place the stone." << endl;
                cout << "Stones must be in this format: " << endl;
                cout << "color(B for black, W for white)y coordinate(starting from A to A + size - 1)x coordinate(size~1)" << endl;
                cout << "All the letters must be capital" << endl;
                cout << "Or you can choose to skip by pressing P for pass" << endl;
                cout << "For example:  BA1   WB10   BP   WP" << endl;
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
            case 9:
                game.displayRecord();
                break;
            default:
                break;
        }
    }






    return 0;

}
