// LetterTileDef.cpp
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
//purpose: Provides default constructor and constructor with arguments
// as well as a less-than comparison operator for use in sorting.

#include "stdafx.h"
#include "LetterTileDef.h"


LetterTileDef::LetterTileDef(): count(0) {
}

LetterTileDef::LetterTileDef(const LetterTile & tile, const unsigned int count) : tile(tile), count(count)
{	
}

bool LetterTileDef::operator< (const LetterTileDef &ltd) const {
	if (this->count < ltd.count) {
		return true;
	}
	if ((this->count == ltd.count) && (this->tile.letter < ltd.tile.letter)) {
		return true;
	}
	return false;

}