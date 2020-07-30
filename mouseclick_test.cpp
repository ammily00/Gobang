#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

Mat frame;
Point pt(-1,-1);
Point point;
bool newCoords = false;

void mouse_callback(int  event, int  x, int  y, int  flag, void *param){
    if (event == EVENT_LBUTTONDOWN){
        // Store point coordinates
        pt.x = x;
        pt.y = y;
        newCoords = true;
    }
}

int main(int, char**){

    bool wrongPos = false;
    namedWindow("img", 1);
    Mat board = imread("1919board.png");
    Mat blackstone = imread("blackstone.png");
    Mat whitestone = imread("whitestone.png");

    // for (point.x = 22;point.x<=board.cols-5;point.x+=((point.x>22+36*4&&point.x<22+36*13)?37:36)){
    //     for (point.y = 22;point.y<=board.rows-5;point.y+=((point.y>22+36*4&&point.y<22+36*13)?37:36)){
    //         circle(board, point, 3, Scalar(255, 0, 0));
    //     }      
    // }
    

    // Set callback
    setMouseCallback("img", mouse_callback);

    //for (;pt.x < 688 && pt.y < 688 && pt.x > 15 && pt.y > 15;){
    for (;;){

        //if (pt.x != -1 && pt.y != -1){
        if (pt.x != -1 && pt.y != -1 && pt.x < 688 && pt.y < 688 && pt.x > 15 && pt.y > 15){    
            if (pt.x<=22+36*4){
                if ((pt.x-22) % 36 <= 10)
                    pt.x -= (pt.x-22) % 36;
                else if ((pt.x-22) % 36 >= 27)
                    pt.x = ((pt.x-22) / 36 + 1) * 36 + 22;
                else
                    wrongPos = true; 
            }
            else if (pt.x>22+36*4 && pt.x<22+36*13){
                if ((pt.x-22-36*4) % 37 <= 10)
                    pt.x -= (pt.x-22-36*4) % 37;
                else if ((pt.x-22-36*4) % 37 >= 27)
                    pt.x = (((pt.x-22-36*4)) / 37 + 1) * 37 + 36*4 + 22;
                else
                    wrongPos = true;
            }
            else{ // pt.x>=22+36*13
                if ((pt.x-22-36*4-37*8) % 36 <= 10)
                    pt.x -= (pt.x-22-36*4-37*8) % 36;
                else if ((pt.x-22-36*4-37*8) % 36 >= 27)
                    pt.x = ((pt.x-22-36*4-37*8) / 36 + 1) * 36 + 37*8 + 36*4 + 22;
                else
                    wrongPos = true;
            }

            if (pt.y<=22+36*4){
                if ((pt.y-22) % 36 <= 10)
                    pt.y -= (pt.y-22) % 36;
                else if ((pt.y-22) % 36 >= 27)
                    pt.y = ((pt.y-22) / 36 + 1) * 36 + 22;
                else
                    wrongPos = true; 
            }
            else if (pt.y>22+36*4 && pt.y<22+36*13){
                if ((pt.y-22-36*4) % 37 <= 10)
                    pt.y -= (pt.y-22-36*4) % 37;
                else if ((pt.y-22-36*4) % 37 >= 27)
                    pt.y = (((pt.y-22-36*4)) / 37 + 1) * 37 + 36*4 + 22;
                else
                    wrongPos = true;
            }
            else{ // pt.y>=22+36*13
                if ((pt.y-22-36*4-37*8) % 36 <= 10)
                    pt.y -= (pt.y-22-36*4-37*8) % 36;
                else if ((pt.y-22-36*4-37*8) % 36 >= 27)
                    pt.y = ((pt.y-22-36*4-37*8) / 36 + 1) * 36 + 37*8 + 36*4 + 22;
                else
                    wrongPos = true;
            }

            if (!wrongPos) {
                //circle(board, pt, 3, Scalar(0, 0, 255));
                blackstone.copyTo(board(Rect(pt.x-blackstone.cols/2,pt.y-blackstone.rows/2,blackstone.cols, blackstone.rows)));
            } 
                
            else
                wrongPos = false;
            

            if (newCoords){
                std::cout << "Clicked coordinates: " << pt << std::endl;
                newCoords = false;
            }
        }

        imshow("img", board);

        // Exit if 'q' is pressed
        if ((waitKey(1) & 0xFF) == 'q') break;
    }

    return 0;
}