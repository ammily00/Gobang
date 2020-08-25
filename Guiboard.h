#ifndef GUIBOARD_H_
#define GUIBOARD_H_
#include <opencv2/opencv.hpp>
#include "Board.h"

class Guiboard : public Board {
public:
    Guiboard(int size);
    ~Guiboard();
    cv::Point stone2pixel(int x, int y);
    void printBoard();
    friend class Guigame;
private:
    /*
     * the size (size*size) of the board
     */
    int size;

};

#endif /* GUIBOARD_H_ */
