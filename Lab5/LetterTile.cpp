// LetterTile.cpp
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
// Purpose:  Defines default constructor and constructor that takes
// a letter and score for the LetterTile struct.  Also defines
// a less than operator for sorting purposes.


#include "stdafx.h"
#include "LetterTile.h"


LetterTile::LetterTile(): letter(0), score(0){
}
LetterTile::LetterTile(const char letter, const unsigned int score) : letter(letter), score(score)
{
}

bool LetterTile::operator < (LetterTile & other)
{
	return letter < other.letter;
}