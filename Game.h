#ifndef GAME_H_
#define GAME_H_
//#define N 15
using namespace std;

class Stone{
    int x;
    int y;
    char color; //x for black, o for white
};

class Board{
    vector<Stone> stone;
    void printBoard();
    friend class Game;
};

class Player{
    int validPoint(const Stone &);
    void playGameInput(const Stone &, int, char);
    void playGame(const Stone &, int, char);
    void checkVictory();
    friend class Game;
};

class Game {
private:

public:
    Game();
    void play();
};

#endif /* GAME_H_ */
