#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(int size){
    size = 15; //could be changed if needed
    resetBoard();
}

Board::~Board(){

}

void Board::printBoard(){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            //print the index number for rows
            if (j == 0)
                cout << i+1 << " ";

            //print the stones for different situations
            switch(grid[i][j]){
                case stoneBlack:
                    cout << "x ";
                    break;
                case stoneWhite:
                    cout << "o ";
                    break;
                default:
                    cout << "  ";
                    break;
            }

            //print the newline when the current line ends
            if (j == size - 1)
                cout << endl;
        }
    }

    //print the index number for columns
    for (char k = 'A'; k < 'A' + size; k++){
        if (k == 'A')
            cout << "  ";
        cout << k << " ";
        if (k == 'A' + size - 1)
            cout << endl;
    }
}

Stone * Board::getStone(int x, int y){
    if (grid[x][y] == NOSTONE)
        return nullptr;
    else{
            Stone * stone;
            stone.x = x;
            stone.y = y;
            stone.color = grid[x][y];
            return stone;
    }
}

void Board::placeStone(int x, int y, stoneColor color){
    grid[x][y] = color;
}

void Board::removeStone(int x, int y){
    grid[x][y] = NOSTONE;
}

void Board::resetBoard(){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            grid[i][j] == NOSTONE;
        }
    }
}