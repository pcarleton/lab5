// LetterTileCollection.h
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
// Purpose: Declares a class for a collection of LetterTiles.
// Supports default constructor, construction from a tiledef
// file, as well as copy construction.  
//
// Also supports a modified copy constructor that copies the 
// collection from the beginning to the specified index.
//
// Supports random shuffling of the LetterTiles container, as well
// moving letter tiles from one collection to another.  Also supports
// finding the next greater permutation of the letter tiles and sorting
// the letter tiles by character.

#ifndef LTC
#define LTC

#include <iostream>
#include <vector>
#include <string>
#include "LetterTile.h"

using namespace std;

class LetterTileCollection {
public:
	LetterTileCollection();
	LetterTileCollection(const LetterTileCollection &);
	LetterTileCollection(const char *);
	LetterTileCollection(const LetterTileCollection &, unsigned int);
	LetterTileCollection(const vector<LetterTile>);
	
	int subCopy(string & input, LetterTileCollection & other);
	void addVect(vector<LetterTile>);

	LetterTileCollection & operator= (const LetterTileCollection &);
	unsigned int size() const;
	int add(const char * filename);
	void move(LetterTileCollection &, unsigned int);
	void print(ostream& = cout) const;

	bool operator== (const LetterTileCollection &) const;
	bool operator< (const LetterTileCollection &) const;

	

	void shuffle();

	bool permute();
	void sortLets();

	string as_string() const;
	int score() const;

	vector<LetterTile> getLetters() const;

private:
	vector<LetterTile> letters;

};


#endif