#ifndef BOARD_H_
#define BOARD_H_

using namespace std;

class Board{
private:
    vector<Stone> stone; // all the stones placed
    int dimension; //n*n board
    void initBoard(); //initialize the board
    void updateBoard(); //every time places a stone, update the board

public:
    Board();
    void printBoard(); //show the sequential order of all the stones
};


#endif /* BOARD_H_ */
