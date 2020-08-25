#include <iostream>
#include "Guiboard.h"

using namespace std;
using namespace cv;

Guiboard::Guiboard(int size) : Board(size) {
    this->size = size;
    // grid = new Stone * [size];
    // for(int i = 0; i < size; i++)
    //     grid[i] = new Stone[size];
    resetBoard();
}

Guiboard::~Guiboard() {  
    // cout << "!!!!!!!!!!!!!!!!!!!!!!! guiboard destructor begins" << endl;
    // for(int i = 0; i < size; i++)
    //     delete[] grid[i];
    // delete[] grid;
    // cout << "!!!!!!!!!!!!!!!!!!!!!!! guiboard destructor ends" << endl; 
}

Point Guiboard::stone2pixel(int x, int y) {
    Point pt;
    if (x <= 4)
        pt.x = 22+36*x;
    else if (x > 4 && x < 12)
        pt.x = 22+36*4+37*(x-4);
    else // x >= 12
        pt.x = 22+36*4+37*8+36*(x-12);

    if (y <= 4)
        pt.y = 22+36*y;
    else if (y > 4 && y < 12)
        pt.y = 22+36*4+37*(y-4);
    else // x >= 12
        pt.y = 22+36*4+37*8+36*(y-12);

    return pt;
}

void Guiboard::printBoard(){
    //namedWindow("gobang board", 1);
    Mat board = imread("1919board.png");
    Mat blackstone = imread("blackstone.png");
    Mat whitestone = imread("whitestone.png");

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            Point pt = stone2pixel(i, j);
            //cout << grid[i][j].x << " " << grid[i][j].y  << " " << grid[i][j].color << endl;
            //print the stones for different situations
            switch(grid[i][j].color){
                case stoneBlack:
                    blackstone.copyTo(board(Rect(
                        pt.x-blackstone.cols/2,pt.y-blackstone.rows/2,
                        blackstone.cols, blackstone.rows)));
                    break;
                case stoneWhite:
                    whitestone.copyTo(board(Rect(
                        pt.x-whitestone.cols/2,pt.y-whitestone.rows/2,
                        whitestone.cols, whitestone.rows)));
                    break;
                default:
                    break;
            } 
        }
    }

    imshow("gobang board", board);
    waitKey(0);
}