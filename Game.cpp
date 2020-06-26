#include "Gomoku.h"
#include <iostream>
using namespace std;

Game::Game(){

}

Game::~Game(){

}

/*
void Gomoku::initChessBoard(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            chessboard[i][j] = '.';
        }
    }
}

int Gomoku::validPoint(const Point & point){
    if (point.x > 0 && point.x <= N && point.y > 0 && point.y <= N){ //within the chessboard
        if (chessboard[point.x][point.y] == '.') //do not have piece
            return 0; //valid
    }
    return -1; //invalid
}

void playChessInput(const Point & point, int player, char piece){
    printChessBoard();
    while(1){
        cout << "It is player" << player << "\'s turn" << endl; //player1 or player2
        cin >> point.x >> point.y;
        if (validPoint(point) == 0) //valid
            break;
        cout << "Invalid point, please input again!" << endl;
    }
    chesscoard[point.x][point.y] = piece; //'o' for player1 and 'x' for player2
}

void playChess(const Point & point, int player, char piece){
    playChessInput(point, player, piece);
}

void Gomoku::printChessBoard(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout << chessboard[i][j];
            if (j == N-1)
                cout << endl;
        }
    }
}

void Gomoku::judge(const Point & point, int player, char piece){

}

void Gomoku::play(){
    Point player1;
    Point player2;
    while(1){
        playChess(player1, 1, 'o');
        playChess(player2, 2, 'x');
        cout << "Want to start a new game? default yes, press n for no" << endl;
        char start_new;
        cin >> start_new;
        if (start_new == 'n')
            break;
    }

}
*/