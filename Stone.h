#ifndef STONE_H_
#define STONE_H_

typedef enum {
    stoneBlack,
    stoneWhite
} stoneColor;

class Stone {
public:


private:

    /*
     * x coordinate
     */
    int x;

    /*
     * y coordinate
     */
    int y;

    /*
     * color of the stone
     */
    stoneColor color;
};

#endif /* STONE_H_ */
