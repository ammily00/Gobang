#include "Guigame.h"

using namespace std;
using namespace cv;

Guigame::Guigame(int size) : Game(size), guiboard(size) {
    this->size = size;
    moveNum = 0;
    tryStoneMoveNum = 0;
    pt.x = -1;
    pt.y = -1;
}

Guigame::~Guigame() {
    moves.clear();
    tryStoneMoves.clear();
}

Point Guigame::getPoint() {
    return pt;
}

void Guigame::pointTrans(Point &pt) {
    bool wrongPos = false;

    if (pt.x != -1 && pt.y != -1 && pt.x < 688 && pt.y < 688 && pt.x > 15 && pt.y > 15) {
        if (pt.x <= 22+36*4) {
            if ((pt.x-22)%36 <= 10)
                pt.x -= (pt.x-22)%36;
            else if ((pt.x-22)%36 >= 27)
                pt.x = ((pt.x-22)/36+1)*36+22;
            else
                wrongPos = true;
        }
        else if (pt.x > 22+36*4 && pt.x < 22+36*4+37*8) {
            if ((pt.x-22-36*4)%37 <= 10)
                pt.x -= (pt.x-22-36*4)%37;
            else if ((pt.x-22-36*4)%37 >= 27)
                pt.x = (((pt.x-22-36*4))/37+1)*37+36*4+22;
            else 
                wrongPos = true;
        }
        else { // pt.x>=22+36*4+37*8
            if ((pt.x-22-36*4-37*8)%36 <= 10)
                pt.x -= (pt.x-22-36*4-37*8)%36;
            else if ((pt.x-22-36*4-37*8)%36 >= 27)
                pt.x = ((pt.x-22-36*4-37*8)/36+1)*36+37*8+36*4+22;
            else
                wrongPos = true;
        }

        if(pt.y <= 22+36*4){
            if((pt.y-22)%36 <= 10)
                pt.y -= (pt.y-22)%36;
            else if((pt.y-22)%36 >= 27)
                pt.y = ((pt.y-22)/36+1)*36+22;
            else
                wrongPos = true;
        }
        else if(pt.y>22+36*4&&pt.y<22+36*4+37*8){
            if((pt.y-22-36*4)%37 <= 10)
                pt.y -= (pt.y-22-36*4)%37;
            else if((pt.y-22-36*4)%37 >= 27)
                pt.y = (((pt.y-22-36*4))/37+1)*37+36*4+22;
            else
                wrongPos = true;
        }
        else{//pt.y >= 22+36*4+37*8
            if((pt.y-22-36*4-37*8)%36 <= 10)
                pt.y -= (pt.y-22-36*4-37*8)%36;
            else if((pt.y-22-36*4-37*8)%36 >= 27)
                pt.y = ((pt.y-22-36*4-37*8)/36+1)*36+37*8+36*4+22;
            else
                wrongPos = true;
        }
    }
    else
        wrongPos = true;

    if (wrongPos) {
        pt.x = -1;
        pt.y = -1;
    }
}

Move * Guigame::point2move(Point pt) {
    Move * point = new Move;

    if (pt.x <= 22 + 36*4) 
        point->x = (pt.x-22)/36;
    else if (pt.x > 22 + 36*4 && pt.x < 22 + 36*4 + 37*8)
        point->x = 4 + (pt.x-22-36*4)/37;
    else // pt.x>=22+36*4+37*8
        point->x = 4 + 8 + (pt.x-22-36*4-37*8)/36;

    if (pt.y <= 22 + 36*4)
        point->y = (pt.y-22)/36;
    else if (pt.y > 22 + 36*4 && pt.y < 22 + 36*4 + 37*8)
        point->y = 4 + (pt.y-22-36*4)/37;
    else // pt.y>=22+36*4+37*8
        point->y = 4 + 8 + (pt.y-22-36*4-37*8)/36;

    return point;
}

void Guigame::moveStone(Point pt) {
    if (getGameStatus() == GameEnd)
        return;  
    pointTrans(pt);
    if (pt.x != -1 && pt.y != -1) {
        Move * moveAStone = point2move(pt);
        if (moveNum % 2 == 1)
            moveAStone->color = stoneWhite;
        else // moveNum % 2 == 0
            moveAStone->color = stoneBlack;
    
        Stone * intersection = guiboard.getStone(moveAStone->x, moveAStone->y);
        // no stone in this intersection
        if (intersection == nullptr) {
            guiboard.placeStone(moveAStone->x, moveAStone->y, moveAStone->color);
            moveAStone->seqNum = ++moveNum;
            moves.push_back(*moveAStone);

            int result = checkVictory(guiboard.grid, moveAStone->x, 
                                      moveAStone->y, moveAStone->color);
            //cout << result << endl;
            if (result == moveAStone->color) {
                if (moveAStone->color == stoneBlack)
                    cout << "Black wins!" << endl;
                else if (moveAStone->color == stoneWhite)
                    cout << "White wins!" << endl;
                status = GameEnd;
                return;
            }
            if (guiboard.fullBoard() == true && result == -1){
                cout << "standoff" << endl;
                status = GameEnd;
                return;
            }
        }
        else{
            if (intersection->color == stoneBlack)
                cout << "A black stone has been placed at "
                     << char('A'+moveAStone->x) << size-moveAStone->y << endl << endl;
            else if (intersection->color == stoneWhite)
                cout << "A white stone has been placed at "
                     << char('A'+moveAStone->x) << size-moveAStone->y << endl<< endl;
        }
    }
    return;
}

void Guigame::printGame(){
    guiboard.printBoard();
}

void Guigame::replayStone(){
    guiboard.resetBoard();
    guiboard.printBoard();
    for (vector<Move>::iterator it = moves.begin(); it != moves.end(); it++){
        if (it->x != -1 && it->y != -1) //make sure it is a real stone instead of passing
            guiboard.placeStone(it->x, it->y, it->color);

        time_t start;
        start = time(0);
        int n = 1; //1 second
        while(1){
            if(time(0) - start == n) {//print every n second(s)
                guiboard.printBoard();
                //cout << it->x << it->y << it->color << endl;
                start = start + n;
                break;
            }
        }
    }
}
/*
int Guigame::checkVictory(int x, int y, stoneColor color){ 
    // check whether there are five sequential stones in the same color as the stone passed in 
    bool win = false; 
    // true means that the stone passed in is in the five sequential stones in this row/column/diagonal 
    bool found = false; 
 
    // row 
    for (int j = 0; j < size; j++){ 
        if (j < size - 4) { 
            if (guiboard.grid[x][j].color == color && guiboard.grid[x][j+1].color == color && 
                guiboard.grid[x][j+2].color == color && guiboard.grid[x][j+3].color == color && 
                guiboard.grid[x][j+4].color == color) 
                win = true; 
            if (y == j || y == j+1 || y == j+2 || y == j+3 || y == j+4) 
                found = true; 
            if (win == true && found == true){ 
                win = false; 
                found = false; 
                return color; 
            } 
            else{ 
                win = false; 
                found = false; 
            } 
        } 
 
    } 
 
    // column 
    for (int i = 0; i < size; i++){ 
        if (i < size-4) { 
            if (guiboard.grid[i][y].color == color && guiboard.grid[i+1][y].color == color && 
                guiboard.grid[i+2][y].color == color && guiboard.grid[i+3][y].color == color && 
                guiboard.grid[i+4][y].color == color) 
                win = true; 
            if (x == i || x == i+1 || x == i+2 || x == i+3 || x == i+4) 
                found = true; 
            if (win == true && found == true){ 
                win = false; 
                found = false; 
                return color; 
            } 
            else{ 
                win = false; 
                found = false; 
            } 
        } 
    } 
 
    // diagonal (left top to right bottom) 
    if (x <= y){ 
        for (int i = 0, j = y-x; i < size-y+x && j < size; i++, j++){ 
            if (y-x < size-4){ // the diagonal has at least 5 intersections 
                if (j < size-4){ 
                    if (guiboard.grid[i][j].color == color && guiboard.grid[i+1][j+1].color == color && 
                        guiboard.grid[i+2][j+2].color == color && guiboard.grid[i+3][j+3].color == color && 
                        guiboard.grid[i+4][j+4].color == color) 
                        win = true; 
                    if ((x == i && y == j) || (x == i+1 && y == j+1) || (x == i+2 && j == i+2) || 
                        (x == i+3 && y == j+3) || (x == i+4 && y == j+4)) 
                        found = true; 
                    if (win == true && found == true){ 
                        win = false; 
                        found = false; 
                        return color; 
                    } 
                    else{ 
                        win = false; 
                        found = false; 
                    } 
                } 
            } 
        } 
    } 
    else{ // x > y 
        for (int i = x-y, j = 0; i < size && j < size-x+y; i++, j++){ 
            if (x-y < size-4){ // the diagonal has at least 5 intersections 
                if (i < size-4){ 
                    if (guiboard.grid[i][j].color == color && guiboard.grid[i+1][j+1].color == color && 
                        guiboard.grid[i+2][j+2].color == color && guiboard.grid[i+3][j+3].color == color && 
                        guiboard.grid[i+4][j+4].color == color) 
                        win = true; 
                    if ((x == i && y == j) || (x == i+1 && y == j+1) || (x == i+2 && j == i+2) || 
                        (x == i+3 && y == j+3) || (x == i+4 && y == j+4)) 
                        found = true; 
                    if (win == true && found == true){ 
                        win = false; 
                        found = false; 
                        return color; 
                    } 
                    else{ 
                        win = false; 
                        found = false; 
                    } 
                } 
            } 
        } 
    } 
 
    // diagonal (right top to left bottom) 
    if (x+y < size){ 
        for (int i = 0, j = x+y; i <= x+y && j >= 0; i++, j--){ 
            if (x+y >= 4){ // the diagonal has at least 5 intersections 
                if (i <= x+y-4){ 
                    if (guiboard.grid[i][j].color == color && guiboard.grid[i+1][j-1].color == color && 
                        guiboard.grid[i+2][j-2].color == color && guiboard.grid[i+3][j-3].color == color && 
                        guiboard.grid[i+4][j-4].color == color) 
                        win = true; 
                    if ((x == i && y == j) || (x == i+1 && y == j-1) || (x == i+2 && j == i-2) || 
                        (x == i+3 && y == j-3) || (x == i+4 && y == j-4)) 
                        found = true; 
                    if (win == true && found == true){ 
                        win = false; 
                        found = false; 
                        return color; 
                    } 
                    else{ 
                        win = false; 
                        found = false; 
                    } 
                } 
            } 
        } 
    } 
    else{ // x+y >= size 
        for (int i = x+y-size+1, j = size-1; i < size && j > x+y-size; i++, j--){ 
            // the last one: starting from (size-5, size-1) to (size-1, size-5), sum is 2*size-6 
            if (x+y <= 2*size-6){ // the diagonal has at least 5 intersections 
                if (i < size-4){ 
                    if (guiboard.grid[i][j].color == color && guiboard.grid[i+1][j-1].color == color && 
                        guiboard.grid[i+2][j-2].color == color && guiboard.grid[i+3][j-3].color == color && 
                        guiboard.grid[i+4][j-4].color == color) 
                        win = true; 
                    if ((x == i && y == j) || (x == i+1 && y == j-1) || (x == i+2 && j == i-2) || 
                        (x == i+3 && y == j-3) || (x == i+4 && y == j-4)) 
                        found = true; 
                    if (win == true && found == true){ 
                        win = false; 
                        found = false; 
                        return color; 
                    } 
                    else{ 
                        win = false; 
                        found = false; 
                    } 
                } 
            } 
        } 
    } 
    return -1; 
}
*/