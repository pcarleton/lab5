#ifndef PLAYER_H
#define PLAYER_H

#include "LetterTileCollection.h"
#include <string>

using namespace std;

class Player{
public:
	Player();
	Player(string &);
	bool operator ==(const Player &) const;
	int numTiles();
	void receiveTiles(LetterTileCollection &, int);
	void showTiles(ostream & = cout);
	int getScore();
	void addScore(int);
	int checkString(string &, LetterTileCollection &);
	string getName();
	virtual int getPlayChoice();
	LetterTileCollection & getTileCollection();
private:
	string name;
	LetterTileCollection tileCollection;
	unsigned int score;
};

#endif