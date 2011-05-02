#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "LetterTileCollection.h"
#include "GameBoard.h"
#include "PlayOptions.h"

using namespace std;

class GameBoard;

class Player{
public:

	virtual ~Player();
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
	virtual PlayOptions obtainPlayOptions(GameBoard &);
protected:
	string name;
	LetterTileCollection tileCollection;
	unsigned int score;
};

#endif