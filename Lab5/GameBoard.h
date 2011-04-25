//Gameboard.h
//
//Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
//Purpose: Declare methods for a GameBoard class which
// handles the arrangement of letter tiles for a game
// of Solitaire Scrabble.


#ifndef GAMEBOARD
#define GAMEBOARD
#include "Lab5.h"
#include "LetterTile.h"
#include <map>
#include <utility>
#include <iostream>
#include <fstream>
#include "Dictionary.h"
#include "LetterTileCollection.h"

#define MIN_COORD -7
#define MAX_COORD 7
#define INVALID_PLAY 0
#define EMPTY_POINTER 0

using namespace std;

class GameBoard {
private:
	const Dictionary * dict;
	map<pair<int,int>,LetterTile*> cells;

	set<pair<int,int>> dl;
	set<pair<int,int>> tl;
	set<pair<int,int>> dw;
	set<pair<int,int>> tw;
	
	bool checkIntersect(pair<int, int>, direction, int);
	bool tilePresent(int, int);

	bool checkBounds(pair<int,int>, int, direction);
	
	string checkCell(pair<int,int>);
	

	int checkWords(pair<int, int>, direction);
	direction oppDir(const direction &);

	bool placeTiles(const LetterTileCollection & ltc, direction dir, 
						   vector<pair<int,int>> & placedTiles, pair<int, int> coords);
	void removeInvalidTiles(vector<pair<int,int>> & tiles);
	void eraseMultipliers(vector<pair<int,int>> &, set<pair<int,int>> &);

	
public:
	//Suggesting is defaulted to false.  This argument specifies if the game is "suggesting" plays
	//and ensures that no tiles actually get placed.
	int play(const LetterTileCollection &, const pair<int, int> &,const direction, bool suggesting = false); 
	bool checkBounds(pair<int,int>);
	GameBoard();
	GameBoard(const Dictionary *);
	void print(ostream &);
	void showPossiblePlays(LetterTileCollection &);
	int addSpecialCells(const char *);
};


#endif