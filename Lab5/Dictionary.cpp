// Dictionary.cpp
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
//Purpose:  Define methods and constructors for dictionary class
// for use in Scrabble.  Has set of words.  Can add words to the set
// from a file, can return size of set, and can tell if a word is in
// set.


#include "stdafx.h"
#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;


//Default constructor, initiliazes words to be empty.
Dictionary::Dictionary(): words() {
}

// Constructor taking in file name.  Adds words from file
// to set of words.
Dictionary::Dictionary(const char * fname): words() {
	add(fname);
}

//Reads in words from file and adds to "words" set.
int Dictionary::add(const char * fname) {
	ifstream ifs (fname);
	if (ifs.is_open())
	{
		string temp;

		//Reads in words from dictionary file and adds them to set.
		while (ifs >> temp)
		{
			transform(temp.begin(), temp.end(),temp.begin(), ::tolower);
			words.insert(temp);
		}

		return SUCCESS;

	} else {
		//Returns 2 if unable to open dictionary file
		cout << "Error in opening dictionary file in read_dict " << endl;
		return READ_DICT_ERR;
	}
}


int Dictionary::size() const {
	return words.size();
}

void Dictionary::print(ostream& os) const {
	for (set<string>::const_iterator it = words.begin(); it != words.end(); ++it)
	{
		os << *it << endl;
	}
}

//Returns true if "query" is contained in words
bool Dictionary::find(const string query) const
{
	return (words.find(query) != words.end());
}

