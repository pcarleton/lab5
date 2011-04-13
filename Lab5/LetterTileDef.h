// LettertileDef.h
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
//Purpose:  Declaration for a Letter Tile Definition struct which 
// has a letter tile, and a countof how many times that letter appeared in the
// dictionary.  It also defines a less than operator for use in sorting in 
// order to determine what score a letter tile should have.
// 
//


#ifndef LETTER_TILE_DEF
#define LETTER_TILE_DEF
#include "LetterTile.h"

struct LetterTileDef {
	LetterTile tile;
	unsigned int count;

	//Default constructor
	LetterTileDef();

	LetterTileDef(const LetterTile &, const unsigned int);


	//Less than operator for sorting
	bool operator< (const LetterTileDef &) const;

};

#endif
