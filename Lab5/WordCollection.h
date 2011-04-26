// WordCollection.h
//
// Author: Paul Carleton -- paulcarleton@wustl.edu
//
// Purpose: A collection of words that can be created from a given
//  LetterTileCollection.  A word is deemed valid if it is contained
//  in the passed Dictionary class.
//
//  This is achieved by going through each permutation of the LTC and
//  checking if the word is contained.  Permutation in this case means
//  every possible ordering of every possible size.
//
//  Note: Copy constructor is provided since a WordCollection object
//  may need to be copied in the future, and there's no intrinsic 
//  reason that it shouldn't be able to be copied.


#ifndef WORD_COLLECTION
#define WORD_COLLECTION
#include "LetterTileCollection.h"
#include "Dictionary.h"
#include <iostream>
#include <vector>

class WordCollection {
public:
	WordCollection();
	WordCollection(const LetterTileCollection &, const Dictionary &);
	WordCollection(const WordCollection &);
	void print(ostream & os = std::cout) const;

private:
	vector<LetterTileCollection> ltcols;
};


#endif