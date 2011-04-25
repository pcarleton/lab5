// LetterTileCollection.cpp
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
// Purpose:  Defines functions for a LetterTileCollection class
// as specified in "LetterTileCollection.h"

#include "stdafx.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "LetterTileCollection.h"

//Default constructor, initiliazes container of lettertiles to empty
LetterTileCollection::LetterTileCollection(): letters() {
}

//Adds letter tiles from file
LetterTileCollection::LetterTileCollection(const char * fname): letters() {
	add(fname);
}

//Copy constructor, sets this container to match that of the LTC passed
LetterTileCollection::LetterTileCollection(const LetterTileCollection & other): letters(other.letters) {
}

//Modified copy constructor that only copies LT's from the beginning to the index specified.
LetterTileCollection::LetterTileCollection(const LetterTileCollection & other, unsigned int index)
: letters() {
	if (index > other.letters.size()) {
		index = other.letters.size();
	}
	//POINTER ARITHMETIC EXPLANATION: I'm adding index to other.letters.begin()
	//so it makes it from the beginning to the index specified.
	letters = vector<LetterTile>(other.letters.begin(),other.letters.begin()+index);
}

//Constructor that takes a vector of LetterTiles
LetterTileCollection::LetterTileCollection(const std::vector<LetterTile> lts): letters(lts){
}

void LetterTileCollection::addVect(vector<LetterTile> vect) {
	letters.insert(letters.end(), vect.begin(), vect.end());
}

// add given letters to the LTC passed by reference, and remove them from the source LTC.
// returns -1 if the string is not contained in the source LTC.
int LetterTileCollection::subCopy(string & input, LetterTileCollection & other) {
	vector<LetterTile> subLets;
	bool found = false;
	for (string::iterator inIter = input.begin(); inIter != input.end(); ++inIter)
	{
		found = false;
		for (vector<LetterTile>::iterator letIter = letters.begin(); letIter != letters.end(); ++letIter)
		{
			if (*inIter == letIter->letter) {
				subLets.push_back(*letIter);
				letters.erase(letIter,letIter+1);
				found = true;
				break;
			}
		}
		if (!found) {
			addVect(subLets);
			return -1;
		}
	}
	other.addVect(subLets);
	return 0;
}

//Assignment operator.
LetterTileCollection & LetterTileCollection::operator = (const LetterTileCollection & other) {
	if (this != &other)
	{
		letters.clear();
		letters = other.letters;
	}
	return *this;
}

//Adds Letter Tiles from a definition file
//File specified has format <letter> <score> <count>
// separated by new lines.
int LetterTileCollection::add(const char *filename) {
	ifstream ifs (filename);
	if (ifs.is_open())
	{
		string line;

		//Reads lines in from tiledef file
		while(getline(ifs, line))
		{
			istringstream iss (line);
			int count, score;
			char letter;

			//extracts LetterTile variables from line
			if (iss >> letter >> score >> count)
			{	
				// Convert tile to lowercase
				letter = tolower(letter);
				//Creates count new LetterTiles with extracted variables
				for (int i = 0; i < count; ++i)
				{
					LetterTile temp;
					temp.letter = letter;
					temp.score = score;
					letters.push_back(temp);
				}
			} else {
				//Returns error if the extraction fails
				cout << "Improperly formatted tile defintion file." << endl;
				return TILEDEF_FORMAT_ERR;
			}
		}
		return SUCCESS;
	} else {
		//Returns 3 if unable to open tile definition file
		cout << "Error in opening tile definitions file in read_tiledef." << endl;
		return READ_TILEDEF_ERR;
	}
}

//Moves letter tiles from "other" to this, deleting them from the other.
// If the size specified is greater than the other's size, it copies
// all the tiles in the other collection.
void LetterTileCollection::move(LetterTileCollection & other, unsigned int numTiles) {
	if (numTiles > other.size())
	{
		numTiles = other.size();
	}

	for (unsigned int i = 0; i < numTiles; ++i)
	{
		letters.push_back(other.letters.back());
		other.letters.pop_back();
	}
}


unsigned int LetterTileCollection::size() const {
	return letters.size();
}

//Prints out the letters and scores of each letter tile in collection
void LetterTileCollection::print(ostream & os) const {
	for (vector<LetterTile>::const_iterator it = letters.begin(); it != letters.end(); ++it)
	{
		cout << it->letter << " " << it->score << endl;
	}
}

//Equivalence operator defined if the LTC's have the same letters in the same order.
bool LetterTileCollection::operator ==(const LetterTileCollection & other) const {

	if (size() == other.size())
	{
		bool same = true;
		for (unsigned int i = 0; i < letters.size(); ++i)
		{
			if (letters[i].letter != other.letters[i].letter)
			{
				//If letter's don't match, ltc's not equal
				same = false;
			}
		}
		return same;
	}
	return false;
}

//Less than operator for use in sorting determined by score
bool LetterTileCollection::operator < (const LetterTileCollection & other) const {
	return (score() < other.score());
}

//Adds up the scores of each letter tile in the collection.
int LetterTileCollection::score() const {
	int score = 0;
	for (vector<LetterTile>::const_iterator it = letters.begin(); it != letters.end(); ++it)
	{
		score += it->score;
	}
	return score;
}

//Randomly shuffles the Letter Tile Collection
void LetterTileCollection::shuffle() {
	random_shuffle(letters.begin(),letters.end());
}

//Returns the next lexicographically greater permutation of the Letter tiles.
bool LetterTileCollection::permute() {
	return next_permutation(letters.begin(), letters.end());
}

//Sorts the letter tiles alphabetically
void LetterTileCollection::sortLets() {
	sort(letters.begin(), letters.end());
}

//returns a string represeatntion of the LTC
// concatenating each letter into a single string.
string LetterTileCollection::as_string() const {
	ostringstream oss;
	for (vector<LetterTile>::const_iterator it = letters.begin(); it != letters.end(); ++it)
	{
		oss<< it->letter;
	}
	return oss.str();
}

vector<LetterTile> LetterTileCollection::getLetters() const
{
	return letters;
}