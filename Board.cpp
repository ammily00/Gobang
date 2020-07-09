#include "Board.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Board::Board(int size){
    this->size = size; //size parameter passed in by the user
    grid = new Stone * [size];
    for(int i = 0; i < size; i++)
        grid[i] = new Stone[size];
    resetBoard();
}

Board::~Board(){
    for(int i = 0; i < size; i++)
        delete[] grid[i];
    delete[] grid;
}

void Board::printBoard(){
    system("clear");
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            //print the index number for rows
            if (j == 0)
                cout << size - i << " ";

            //print the stones for different situations
            switch(grid[i][j].color){
                case stoneBlack:
                    cout << "b ";
                    break;
                case stoneWhite:
                    cout << "w ";
                    break;
                default:
                    cout << "· ";
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
    if (grid[x][y].color == NOSTONE)
        return nullptr;
    else
        return * grid;
}

void Board::placeStone(int x, int y, stoneColor color){
    grid[x][y].color = color;
}

void Board::removeStone(int x, int y){
    grid[x][y].color = NOSTONE;
}

void Board::resetBoard(){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            grid[i][j].x = i;
            grid[i][j].y = j;
            grid[i][j].color = NOSTONE;
        }
    }
}