#ifndef PLAYER_H
#define PLAYER_H

#include "LetterTileCollection.h"
#include <string>

using namespace std;

class Player{
public:
	Player(string &);
private:
	string name;
	LetterTileCollection tileCollection;
	unsigned int score;
};

#endif