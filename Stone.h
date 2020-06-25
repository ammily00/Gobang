#ifndef STONE_H_
#define STONE_H_

using namespace std;

class Stone{
private:
    int x; //x coordinate
    int y; //y coordinate
    char color; //x for black, o for white
    int index; //sequential number of the stone
    void initStone(); //initialize the stone
    void placeStone(int, int, char); //place the stone on the board

public:
    Stone();
};

#endif /* STONE_H_ */
