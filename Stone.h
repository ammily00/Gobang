#ifndef STONE_H_
#define STONE_H_

typedef enum {
    stoneBlack,
    stoneWhite
} stoneColor;

class Stone{
public:


private:
    int x; //x coordinate
    int y; //y coordinate
    char color; //x for black, o for white
    int index; //sequential number of the stone


};

#endif /* STONE_H_ */
