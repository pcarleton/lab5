// LetterTile.h
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
//Purpose: declaration for Letter Tile structure for use in Scrabble
// which has a character and an unsigned integer score.

#ifndef LETTER_TILE
#define LETTER_TILE
struct LetterTile {
	char letter;
	unsigned int score;
	LetterTile();
	LetterTile(const char, const unsigned int);
	bool operator< (LetterTile &);
};



#endif