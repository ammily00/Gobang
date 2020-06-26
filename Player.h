#ifndef PLAYER_H_
#define PLAYER_H_

using namespace std;



class Player{
    int validPoint(const Stone &);
    void playGameInput(const Stone &, int, char);
    void playGame(const Stone &, int, char);
    void checkVictory();
    friend class Game;
};



#endif /* PLAYER_H_ */
