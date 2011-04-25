// GameBoard.cpp
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
// Purpose:  Define methods for a GameBoard class for use in
// Solitaire Scrabble.  It keeps track of the current arrangement
// of LetterTiles in a map.  It also handles the authentication and
// scoring of a play.
//
// The coordinate system has (0, 0) in the middle, with (-7, -7) in 
// the top left and (7, 7) the bottom right
//

#include "stdafx.h"
#include "GameBoard.h"
#include <cmath>
#include <sstream>
#include <ctype.h>


//Constructor taking in a file name for a dictionary filename
//Initializes the map of LetterTiles to be empty.
//Note: Min and Max Coords are defined in GameBoard.h
GameBoard::GameBoard(const Dictionary * dict): dict(dict) {
	for (int i = MIN_COORD; i <= MAX_COORD; ++i)
	{
		for (int j = MIN_COORD; j <= MAX_COORD; ++j)
		{
			LetterTile * temp = 0;
			cells.insert(make_pair(pair<int, int>(i, j), temp));
		}
	}
}
//Default constructor initiliazes the board to be empty
GameBoard::GameBoard() {
	for (int i = MIN_COORD; i <= MAX_COORD; ++i)
	{
		for (int j = MIN_COORD; j <= MAX_COORD; ++j)
		{
			LetterTile * temp = 0;
			cells.insert(make_pair(pair<int, int>(i, j), temp));
		}
	}
}

//Prints the current gameboard to the supplied output stream
void GameBoard::print(ostream & os) 
{
	//topBot is the string of numbers that gets displayed
	//on the top and bottom of the board to make picking
	//a coordinate easier to do visually
	stringstream topBot;
	topBot << " ";
	for (int x = MIN_COORD; x <= MAX_COORD; ++x)
	{
		topBot << abs(x);
	}
	char curChar;
	pair<int,int> coord; // current coordinate
	//first print out the topBot screen on top
	os << topBot.str() << endl;
	for (int y = MIN_COORD; y <= MAX_COORD; ++y)
	{
		//Print out the y coordinate on the left side.
		os << abs(y);

		//Print out all of the letters in this row, using space to represent
		//empty spots on the board
		for (int x = MIN_COORD; x <= MAX_COORD; ++x)
		{	
			coord = make_pair(x, y);
			LetterTile * cur = cells.find(coord)->second;
			if ( cur == EMPTY_POINTER)
			{
				if(dl.find(coord) != dl.end())
				{
					os << "-";
					continue;
				}
				if(tl.find(coord) != tl.end())
				{
					os << "+";
					continue;
				}
				if(dw.find(coord) != dw.end())
				{
					os << "*";
					continue;
				}
				if(tw.find(coord) != tw.end())
				{
					os << "^";
					continue;
				}
				os << " ";
			} else {
				//Capitalize the letter
				curChar = toupper(cur->letter);
				os << curChar;
			}
		}

		//Print out the y coordinate again 
		os << abs(y) << endl;
	}
	//Print out the numbers on bottom
	os << topBot.str() << endl;
}

//Attempts to make the specified play, returning the score if successful, 0 otherwise.
//"suggesting" argument is to ensure no tiles are placed if we are suggesting moves
//to the player and defaults to false.
int GameBoard::play(const LetterTileCollection & ltc, 
					const pair<int,int> & coords, const  direction dir, bool suggesting)
{
	//Check if the play intersects a tile (or 0,0 if it's the first play)
	//Return 0 if doesn't work
	if(!checkBounds(coords, ltc.size(), dir))
	{
		if(!suggesting) { cout << "Your word isn't contained in the board." << endl; }
		return INVALID_PLAY;
	}
	if(!checkIntersect(coords, dir, ltc.size()))
	{
		if(!suggesting) { cout << "You can't play there because you didn't intersect any tiles or the origin." << endl; }
		return INVALID_PLAY;
	}
	
	//If we get to this point, the play is possible in terms of 
	//it's coordinates and size.

	//Vector of letter tiles to keep track of where we've placed letter tiles
	//so we can undo the placing later if the play is invalid.
	vector<pair<int,int>> placedTiles;

	//Attempts to place the tiles of the play on the board
	if (!placeTiles(ltc, dir, placedTiles, coords))
	{
		//Remove tiles if it was invalid
		removeInvalidTiles(placedTiles);
		return INVALID_PLAY;
	}
	
	//Checks the word in the direction of the direction parameter
	int totalScore = checkWords(coords, dir);
	
	//If there was no valid score for the main word, remove the tiles and return
	if (totalScore <= INVALID_PLAY)
	{
		removeInvalidTiles(placedTiles);
		return INVALID_PLAY;
	}
	
	//Iterate over all the tiles placed and check that perpendicular words are
	//valid
	int curScore;
	for (vector<pair<int, int>>::iterator iter = placedTiles.begin();
		iter != placedTiles.end(); ++iter)
	{
		//Checks the current tile for words perpendicular to main word
		curScore = checkWords(*iter, oppDir(dir));

		//If there was an invalid word, remove tile and return
		if (curScore < INVALID_PLAY)
		{
			removeInvalidTiles(placedTiles);
			return INVALID_PLAY;
		} else {
			totalScore += curScore;
		}
	}
	
	//Remove all the tiles if we are only trying to suggest possible plays.
	if (suggesting) {
		removeInvalidTiles(placedTiles);
	} else {
		eraseMultipliers(placedTiles, dl);
		eraseMultipliers(placedTiles, tl);
		eraseMultipliers(placedTiles, dw);
		eraseMultipliers(placedTiles, tw);

	}
	return totalScore;
}

//Helper method for returning the opposite direction
direction GameBoard::oppDir(const direction & dir)
{
	if (dir == HORIZONTAL)
	{	
		return VERTICAL;
	} else {
		return HORIZONTAL;
	}
}

string GameBoard::checkCell(pair<int,int> coord)
{
	if(dl.find(coord) != dl.end())
	{
		return "dl";
	}
	if(tl.find(coord) != tl.end())
	{
		return "tl";
	}
	if(dw.find(coord) != dw.end())
	{
		return "dw";
	}
	if(tw.find(coord) != tw.end())
	{
		return "tw";
	}
	return "";
}

// Checks to make sure the word is contained in the dictionary
int GameBoard::checkWords(pair<int, int> start, direction dir)
{
	int * varies;
	if (dir == HORIZONTAL)
	{
		varies = &start.first;
	} else {
		varies = &start.second;
	}
	while (*varies >= MIN_COORD && cells.find(start)->second != 0)
	{
		--(*varies);
	}
	++(*varies);
	vector<LetterTile> curLets;
	//Add letter tiles to current word until we run into an empty space or
	//end of the word

	LetterTile * curTile; 

	while (*varies <= MAX_COORD && cells.find(start)->second != 0)
	{
		
		curTile = cells.find(start)->second;

			//Pushes the letter tile at the coordinate into the vector of letter tiles
			curLets.push_back(*curTile);
			
				
			//Special cell?
			string bonus = checkCell(cells.find(start)->first);

			if(bonus == "tl")
			{
				curLets[curLets.size()-1].score = curLets[curLets.size()-1].score*3;
				cout << "Triple letter score of " << curTile->score << " for " << curTile->letter << "!" << endl;
			}
			if(bonus == "dl")
			{
				curLets[curLets.size()-1].score = curLets[curLets.size()-1].score*2;
				cout << "Double letter score of " << curTile->score << " for " << curTile->letter << "!" << endl;
			}

			bonus = ""; //unset
			++(*varies);
		
	}
	LetterTileCollection curWord(curLets);

	// apply word multpliers

	//If there are no neighbors, return 0
	if (curWord.size() == 1) {
		return 0;
	}
	//If the word is in the dict, return score
	if (dict->find(curWord.as_string())) {
		return curWord.score();
	} else { //Otherwise return -1 to indicate it's not a valid move
		return -1;
	}
	
}

// Places the tiles on the board
// Keeps track of the newly added tile positions in the placedTiles vector
bool GameBoard::placeTiles(const LetterTileCollection & ltc, direction dir, 
						   vector<pair<int,int>> & placedTiles, pair<int, int> coords)
{
	pair<int,int> copy(coords);
	//iterate over passed in letter tiles and place them on the board
	vector<LetterTile> lets = ltc.getLetters();
	for (vector<LetterTile>::iterator iter = lets.begin();
		iter != lets.end(); ++iter)
	{
		while (cells.find(coords)->second != 0)
		{
			if (dir == HORIZONTAL)
			{
				++coords.first;
				if(coords.first > MAX_COORD || coords.first < MIN_COORD) {
					return false;
				}
			} else {
				++coords.second;
				if(coords.second > MAX_COORD || coords.second < MIN_COORD) {
					return false;
				}
			}
		}
		//Try to place tile, return false if we run off the board
		if (!checkBounds(coords))
		{
			return false;
		}
		//WARNING DYNAMIC ALLOCATION
		// It's okay though, because map's destructor calls the destructors
		// on all of its elements.
		LetterTile * temp = new LetterTile(*iter);
		cells.find(coords)->second = temp;

		//Keeps track of letters we placed
		placedTiles.push_back(coords);
	}
	return true;
}

// Makes sure that the new word intersects an already existing word,
// unless it is the first turn, then it makes sure the word
// intersects 0,0
bool GameBoard::checkIntersect(pair<int, int> coords, direction dir, int length)
{
	int varies = 0;
	int fixed = 0;
	
	//assigns which coordinate will vary when checking based on direction
	if (dir == HORIZONTAL)
	{
		varies = coords.first;
		fixed = coords.second;
	} else {
		varies = coords.second;
		fixed = coords.first;
	}
	
	//Checks if this is the first play
	bool firstPlay = (cells.find(make_pair(0, 0))->second == 0);
	
	//If this is the first play, checks if it intersects (0, 0)
	if (firstPlay)
	{
		if (fixed == 0)
		{
			return (varies <= 0 && (varies + length -1) >= 0);
		} else {
			return false;
		}
	}

	//If not first play, checks if the play intersects a tile on the board
	//This for checks tiles played against adjacent oppDir tiles
	for (int i = 0; i < length; ++i)
	{
		if (dir == HORIZONTAL)
		{
			if(tilePresent(varies+i, fixed) || tilePresent(varies+i, fixed-1) || tilePresent(varies+i, fixed+1))
			{
				return true;
			}
		} else {
			if(tilePresent(fixed, varies+i) || tilePresent(fixed-1, varies+i) || tilePresent(fixed+1, varies+i))
			{
				return true;
			}
		}
	}
	// Check tiles before and after word
	if(dir == HORIZONTAL)
	{
		if(tilePresent(varies-1,fixed) || tilePresent(varies+length,fixed))
		{
			return true;
		}
	} else {
		if(tilePresent(fixed,varies-1) || tilePresent(fixed,varies+length))
		{
			return true;
		}
	}
	return false;
}

// Checks if a tile is present at (x,y)
bool GameBoard::tilePresent(int x, int y) 
{
	if(x > MAX_COORD || x < MIN_COORD || y > MAX_COORD || y < MIN_COORD) {
		return false;
	}
	return (cells.find(make_pair(x,y))->second) != 0;
}

// Makes sure that the new word doesn't run off the board
bool GameBoard::checkBounds(pair<int,int> coord, int length, direction dir) {
	int varies = 0;
	int fixed = 0;
	if (dir == HORIZONTAL)
	{
		varies = coord.first;
		fixed = coord.second;
	} else {
		varies = coord.second;
		fixed = coord.first;
	}
	return (varies+(length-1) <= MAX_COORD // word doesn't run off
		&& varies <= MAX_COORD && varies >= MIN_COORD // word starts on board
		&& fixed <= MAX_COORD && fixed >= MIN_COORD); // word starts on board
}

// Makes sure that the coord is contained in the board
bool GameBoard::checkBounds(pair<int,int> coord)
{
	return (coord.first <= MAX_COORD && coord.first >= MIN_COORD // word starts on board
		&& coord.second <= MAX_COORD && coord.second >= MIN_COORD);
}

// If there was an invalid play, it removes the tiles at the positions
// given in the vector "tiles"
void GameBoard::removeInvalidTiles(vector<pair<int,int>> & tiles)
{
	//Removes invalid tyles 
	for (vector<pair<int,int>>::iterator iter = tiles.begin(); iter != tiles.end(); ++iter)
	{
		pair<int, int> coords = *iter;
		cells.find(coords)->second = 0;
		
	}
}

// Generates possible plays from the sequence
void GameBoard::showPossiblePlays(LetterTileCollection & curPlay) {
	int playScore = 0;
	bool someValidPlay = false;
	for(int i = MIN_COORD; i <= MAX_COORD; ++i) {
		for(int j = MIN_COORD; j <= MAX_COORD; ++j) {
			playScore = play(curPlay,make_pair(i,j), HORIZONTAL, true);
			if(playScore > 0) {
				cout << "Play Horizontally at (" << i << ", " << j << ")" << endl;
				someValidPlay = true;
			}
			playScore = play(curPlay,make_pair(i,j), VERTICAL, true);
			if(playScore > 0) {
				cout << "Play Vertically at (" << i << ", " << j << ")" << endl;
				someValidPlay = true;
			}
		}
	}
	if(!someValidPlay) {
		cout << "*** There aren't any possible plays with that sequence, try another. ***" << endl;
	}
}

int GameBoard::addSpecialCells(const char *filename) {
	ifstream ifs (filename);
	pair<int, int> coord;
	int x, y;
	string type;
	if (ifs.is_open())
	{
		string line;

		//Reads lines in from tiledef file
		while(getline(ifs, line))
		{
			istringstream iss (line);

			//extracts LetterTile variables from line
			if (iss >> x >> y >> type)
			{	
				coord = make_pair(x, y);
				if(type == "dl")
				{
					dl.insert(coord);

				}
				if(type == "tl")
				{
					tl.insert(coord);
				}
				if(type == "dw")
				{
					dw.insert(coord);
				}
				if(type == "tw")
				{
					tw.insert(coord);
				}

			} else {
				//Returns error if the extraction fails
				cout << "Improperly formatted special cells file." << endl;
				return SPECIAL_CELLS_FORMAT_ERR;
			}
		}
		return SUCCESS;
	} else {
		//Returns 3 if unable to open tile definition file
		cout << "Error in opening special cells file." << endl;
		return READ_SPECIAL_CELLS_ERR;
	}
}
void GameBoard::eraseMultipliers(vector<pair<int,int>> & locs, set<pair<int,int>> & bonus) {
	for(vector<pair<int,int>>::iterator iter = locs.begin(); iter != locs.end(); ++iter) {
		set<pair<int,int>>::iterator setIter = bonus.find(*iter);
		if(setIter != bonus.end()) {
			bonus.erase(setIter);
		}
	}
}