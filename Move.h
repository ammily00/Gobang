#ifndef MOVE_H_
#define MOVE_H_

#include "Stone.h"

class Move {
public:
    //Move();
    //~Move();

    /*
     * the coordinate and color of the stone passed in by the user
     * in this form: color x_coordinate y_coordinate  or P
     * ex: BH5      WA10
     */
    char cmdString[4];

    /*
     * the record of each step
     * in this form: sequence number:color:x_coordinate:y_coordinate or sequence number:P
     * ex: 1:B:H:5      2:W:A:10    3:P
     */
    char stoneRecord[10];
    /*
     * sequence number
     */
    int seqNum;

    /*
     * x coordinate
     */
    int x;

    /*
     * y coordinate
     */
    int y;

    /*
     * stone color
     */
    stoneColor color;
};

#endif /* MOVE_H_ */
