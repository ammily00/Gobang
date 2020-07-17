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

    cout << "Stones must be in this format: "
            "color(B for black, W for white)y coordinate(starting from A to A + size - 1)x coordinate(size~1)" << endl;
    cout << "Or you can choose to skip by pressing P for pass" << endl;
    cout << "For example:  BA1   WB10   BP   WP" << endl;

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            //print the index number for rows
            if (j == 0){
                if (size < 10){
                    cout << size - i << " ";
                }
                else{
                    if (i > size - 10)
                        cout << size - i << "  ";
                    else
                        cout << size - i << " ";
                }
            }


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
        if (k == 'A'){
            if (size < 10)
                cout << "  ";
            else
                cout << "   ";
        }

        cout << k << " ";
        if (k == 'A' + size - 1)
            cout << endl;
    }
}

Stone * Board::getStone(int x, int y){
    if (grid[x][y].color == NOSTONE)
        return nullptr;
    else
        return * (grid + x) + y;
}

void Board::placeStone(int x, int y, stoneColor color){
    grid[x][y].color = color;
}

void Board::removeStone(int x, int y){
    grid[x][y].color = NOSTONE;
    cout << grid[x][y].color << endl;
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

bool Board::fullBoard(){
    int cnt = 0;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (grid[i][j].color == stoneBlack || grid[i][j].color == stoneWhite)
                cnt++;
        }
    }
    if (cnt == size*size)
        return true;
    return false;
}