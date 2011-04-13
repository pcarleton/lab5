// Dictionary.h
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
// Purpose: Declares a class for storing valid words for a game of scrabble.
//  These words are provided via a file.  The file name can be passed in
// the constructor.  Also words can be added from a file using the add() method.
// The dictionary also supports find() which returns true if the word is found in
// the dictionary.
//
// Dictionary maintains the words in a "set" so only unique words are added and
// so access is quick for calling "find".
//
// The Default destructor is fine for the usage here since this class has no 
// dynamic allocation, so there is no need to call "delete" on anything in the
// destructor.
//
// NOTE: Copy constructor is declared private.  This prevents copying of this
// class since there is no reasonable need to copy a Dictionary at this point
// in time.  Copying would be expensive for a large dictionary file, so it 
// would be better to handle a situation with pointers or references rather
// than copies.


#ifndef DICTIONARY_CLASS
#define DICTIONARY_CLASS
#include "Lab4.h"
#include <set>
#include <string>
#include <iostream>
using namespace std;

class Dictionary {
public:
	Dictionary();

	Dictionary(const char*);
	int add(const char*);
	int size() const;
	void print(ostream& = cout) const;
	bool find(const string) const;
private:
	set<string> words;
	Dictionary(const Dictionary &);
};


#endif