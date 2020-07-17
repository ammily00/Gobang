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
    cout << "Please choose the size of the board, size must be in the range [6, 26] (usually an odd number)" << endl;
    //make sure boardSize is an interger in range [6, 26].
    string boardSize;
    cin >> boardSize;
    cout << endl;
    while (!check_number(boardSize) || stoi(boardSize) < 6 || stoi(boardSize) > 26){
        cout << "\nwrong number, please input again" << endl;
        cin >> boardSize;
        cout << endl;
        if (check_number(boardSize) && stoi(boardSize) >= 6 && stoi(boardSize) <= 26)
            break;
    }

    Game game(stoi(boardSize));

    game.printGame();

    while(1){
        if (game.getGameStatus() == GameEnd){
            cout << "Game ends!" << endl << endl;
            while(1){
                cout << "Please select the number: (Type number directly like 1, 2, or 3)" << endl;
                cout << "1. print the board" << endl;
                cout << "2. replay the game" << endl;
                cout << "3. display stone record" << endl;
                cout << "4. exit" << endl;

                // make sure modeNum is an integer in range [1, 4]
                string modeNum;
                cin >> modeNum;
                if(!check_number(modeNum) || stoi(modeNum) < 1 || stoi(modeNum) > 4) {
                    cout << "\nwrong number, please select again." << endl;
                    continue;
                }

                switch (stoi(modeNum)){
                    case 1:  //print the board
                        game.printGame();
                        break;
                    case 2:  //replay the game
                        game.replayStone();
                        break;
                    case 3: //display stone record
                        game.displayRecord();
                        cout << endl;
                        break;
                    case 4:
                        exit(0);
                    default:
                        break;
                }
            }
        }

        cout << "Please select the number: (Type number directly like 1, 2, or 3)" << endl;
        cout << "1. place a stone" << endl;
        cout << "2. withdraw a stone" << endl;
        cout << "3. place a try-stone" << endl;
        cout << "4. withdraw a try-stone" << endl;
        cout << "5. print the board" << endl;
        cout << "6. replay game" << endl;
        cout << "7. replay try-game" << endl;
        cout << "8. refresh the board" << endl;
        cout << "9. display stone record" << endl;
        cout << "10. exit" << endl;
        // make sure modeNum is an integer in range [1, 10]
        string modeNum;
        cin >> modeNum;
        if(!check_number(modeNum) || stoi(modeNum) < 1 || stoi(modeNum) > 10) {
            cout << "\nwrong number, please select again." << endl;
            continue;
        }

        switch (stoi(modeNum)){
            case 1: //place a stone
                cout << "Please enter the intersection where you want to place the stone." << endl;
                cout << "Black stones must be placed first." << endl;
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
                if (game.moveStone(commandString))
                    game.printGame();
                break;
            case 2: //withdraw a stone
                if (game.getMoveNum() > 0){
                    game.withdrawStone();
                    game.printGame();
                }
                else{
                    game.printGame();
                    cout << "\nNo stone on the board. No stone to withdraw.\n" << endl;
                }
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
                cout << endl;
                break;
            case 10:
                exit(0);
            default:
                break;
        }
    }
    return 0;

}
