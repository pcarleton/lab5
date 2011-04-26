// WordCollection.cpp
//
// Author: Paul Carleton -- paulcarleton@wustl.edu
//
// Purpose:  Defines functions for a WordCollection class as
//  specified in "WordCollection.h"

#include "stdafx.h"
#include "WordCollection.h"
#include "LetterTileCollection.h"
#include "Dictionary.h"
#include <set>
#include <algorithm>

WordCollection::WordCollection() {};

WordCollection::WordCollection(const LetterTileCollection & ltc, const Dictionary & dict): ltcols() {
	
	//Creates local copy of the passed ltc for manipulation.
	LetterTileCollection copyLtc (ltc);

	//Sorts the letter tile collection to ensure it is in its
	//least lexicographical order.
	copyLtc.sortLets();

	//Loop body for checking each permutation of the collection
	// against the dictionary.  Breaks when LetterTileCollection::permute()
	// returns false meaning that it cannot return a lexicographically greater
	// permutation.
	do {
		//Tries each subdivision of the collection
		// as in 0-1, 0-2, 0-3.  Further explanation in readme.
		for (unsigned int i = 0; i < copyLtc.size(); ++i)
		{
			
			LetterTileCollection subCopy (copyLtc,i);
			//If the word is in the dict
			if (dict.find(subCopy.as_string()))
			{
				//and it's not already in "ltcols"
				if (find(ltcols.begin(), ltcols.end(), subCopy) == ltcols.end())
				{
					//add collection to ltcols.
					ltcols.push_back(subCopy);
				}
			}
		}
	} while (copyLtc.permute());

	//Sort the LetterCollections by score for printing
	sort(ltcols.begin(), ltcols.end());
}



void WordCollection::print(ostream & os) const{
	//Print out each LetterCollection's string representation and score.
	for (vector<LetterTileCollection>::const_iterator it = ltcols.begin(); it != ltcols.end(); ++it)
	{	
		cout << it->as_string() << " " << it->score() << endl;
	}
}
WordCollection::WordCollection(const WordCollection & other) : ltcols(other.ltcols) {
}

vector<LetterTileCollection> & WordCollection::getLTCS()
{
	return ltcols;
}