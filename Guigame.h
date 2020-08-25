#ifndef GUIGAME_H_
#define GUIGAME_H_
#include <opencv2/opencv.hpp>
#include "Game.h"
#include "Guiboard.h"

class Guigame : public Game {
public:
    Guigame(int size);
    ~Guigame();
    cv::Point getPoint();
    void moveStone(cv::Point pt);
    void printGame();
    void replayStone();
private:
    Guiboard guiboard;
    int size;
    cv::Point pt;
    void pointTrans(cv::Point & pt);
    Move * point2move(cv::Point pt);
    //int checkVictory(int x, int y, stoneColor color);
};

#endif /* GUIGAME_H_ */
