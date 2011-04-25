// Lab5.cpp : Defines the entry point for the console application.
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
// Purpose: Takes a dictionary file name and a tile definition file name.
//   If the tile def file does not exist, it generates it using the dict-
//   ionary file.  It then creates a LetterTileCollection from the tile
//   definitions file.  For each player it shuffles the main collection
//   and then moves a specified number of tiles into a new collection for
//   each player.  It then creates a Word Collection object to discover
//   all possible words that the player's collection could make where a
//   word is defined by a dictionary.

#include "stdafx.h"
#include "Lab5.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(0))); // seed our random-number generator with the current time
	
	//Useful constants used later.
	const int program_name_index= 0;
	const int numTilesPerPlayer = 7;

	string dict_filename, tiledef_filename;

	//Checks if arguments are valid, and assigns values to the dict and tile
	//def filenames accordingly.
	vector<Player> pnames;
	if (checkArgs(argc, argv, dict_filename, tiledef_filename, pnames))
	{
		int status = runFiles(dict_filename, tiledef_filename);
		if(status != SUCCESS) {
			return status;
		}
	
		//Initializes Dictionary and LTC with the files provided/generated
		Dictionary localDict (dict_filename.c_str());
		LetterTileCollection letterBag(tiledef_filename.c_str());


		GameBoard game(&localDict);
		
		game.addSpecialCells("special_cells.txt");

		bool continuePlaying = true;
		unsigned int numTilesNeeded = 0;
		

		Player * currentPlayer = &pnames[0];
		int currentPlayerIndex = 0;
		int unsuccessfulPlays = 0;
		while(continuePlaying)
		{
			currentPlayer = &pnames[currentPlayerIndex];
			PlayOptions curPlay;
			int playScore = 0;
			int curScore = 0;
			string dirstr;
			pair<int, int> curCoords;

			letterBag.shuffle();
			numTilesNeeded = numTilesPerPlayer - currentPlayer->numTiles();
			currentPlayer->receiveTiles(letterBag, numTilesNeeded);

			cout << "It is " << currentPlayer->getName() << "'s turn." << endl;
			cout << "Current Board " << endl << endl;
			game.print(cout);
			cout << endl << "Current Letters" << endl;
			currentPlayer->showTiles(cout);
			cout << "Current Score: " << currentPlayer->getScore() << endl;

			int playChoice = currentPlayer->getPlayChoice();

			switch(playChoice){
				case 1:
					letterBag.move(currentPlayer->getTileCollection(), currentPlayer->getTileCollection().size());
					letterBag.shuffle();
					currentPlayer->receiveTiles(letterBag, numTilesPerPlayer);
					currentPlayerIndex++;
					unsuccessfulPlays++;
					if(unsuccessfulPlays == pnames.size()) {
						continuePlaying = false;
					}
					break;
				case 2:
					//Do the play.
					curPlay = currentPlayer->obtainPlayOptions(game);
					
					//Process the play

					playScore = game.play(curPlay.tiles, curPlay.coords, curPlay.dir);
					cout << "PLAY SCORE: " << playScore << endl;
					if (playScore <= 0) {
						cout << "That play didn't work" << endl;
						cout << "Possible plays that may work:" << endl;
						game.showPossiblePlays(curPlay.tiles);
						currentPlayer->receiveTiles(curPlay.tiles,curPlay.tiles.size());
						continue;
					} else {
						curScore += playScore;
						//Give the player 50 bonus points for playing all 7 tiles.
						if (currentPlayer->numTiles() == 0) {
							cout << "EXTRA BONUS!!!!" << endl;
							curScore += 50;
						}

						//End the game if there are no letter tiles left in 
						//the bag or the player's collection
						if (letterBag.size() == 0 && currentPlayer->numTiles() == 0) {
							cout << "YOU WIN!" << endl;
							break;
						}
					}
					unsuccessfulPlays = 0;
					currentPlayer->addScore(curScore);
					currentPlayerIndex++;
					break;
				case 3:
					letterBag.move(currentPlayer->getTileCollection(), currentPlayer->getTileCollection().size());
					pnames.erase(pnames.begin()+currentPlayerIndex);
					if(pnames.size() == 1) {
						continuePlaying = false;
					}
					break;
					
				default:
					cout << "That was an invalid choice.";
					break;
				}

				if(currentPlayerIndex == pnames.size()) {
					currentPlayerIndex = 0;
				}
				
			}
			
		return SUCCESS;
	}
//Passes program name argument to usage function to print helpful usage message.
	return usage(argv[program_name_index]);
}


// Preprocesses the dictionary and tile files
int runFiles(string & dict_filename, string & tiledef_filename) {
	//Checks if the dict file specified is valid.
	ifstream dictfs (dict_filename.c_str());
	if (!dictfs.is_open())
	{
		cout << "Invalid Dictionary filename" << endl;
		return INVALID_FILENAME_ERR;
	}
	dictfs.close();
	
	//Checks if the tiledef file is valid.
	ifstream tdfs (tiledef_filename.c_str());
	bool readableTDF = tdfs.is_open();
	tdfs.close();
	
	//If the tiledef file isn't valid, it generates it.
	if (!readableTDF)
	{

		//Declares vector of C++ style strings.  Pass it and the dictionary filename argument
		//to the dictionary reading function.  If function returns non-zero value, program returns it
		//otherwise continies.
		vector<string> dict;
		int err = read_dict(dict, dict_filename.c_str());

		if (err != SUCCESS)
		{
			return err;
		}

		//Declares vector of Letter Tile Definitions then fills the vector from the dictionary using
		//gen_tile_defs
		vector<LetterTileDef> tileDefs;
		gen_tile_defs(dict, tileDefs);

		//attempts to write the Letter Tile Defintions to file using "tile_defs.txt"
		//if no filename was passed as an argument.
		if (tiledef_filename.length() != 0)
		{
			err = write_tile_defs(tileDefs, tiledef_filename.c_str());
		} else
		{
			err = write_tile_defs(tileDefs);
		}

		if (err != SUCCESS)
		{
			return err;
		}
	}
	//Tiledef file has been generated.
	return SUCCESS;
}

//Helper function to print out the usage message
int usage(char * program_name) 
{
	cout << "Usage: " << program_name << " <-d or -D> <dict filename> <-t or -T> <tiledef filename>" << endl;
	cout << "Purpose: Create collections of letter tiles based on the tile definition file" << endl;
	cout << "(if specified, otherwise generates based on dict). Then creates a collections" << endl;
	cout << "for each player and discovers which dictionary defined words it could make." << endl;
	return IMPROPER_ARGS;
}

//Helper functions for determining if args are correct and assigning file names
//to strings to be used in Main
bool checkArgs(int argc, char* argv[], string & dict_filename, string & tiledef_filename, vector<Player> & pnames)
{	
	//Status for telling what we should be looking for next
	enum status {UNKNOWN, DICT, PLAYERS, TILEDEF};

	//initialize status to be unknown
	status s = UNKNOWN;
	string cur, next;
	Player p;
	//booleans to check which inputs we've recieved
	bool dInput = false, tdInput = false, pInput= false;


	//Iterate over all arguments
	for (int i = 1; i < argc; ++i) {
		cur = argv[i];

		//Handle differently based on status
		switch (s)
		{
		case UNKNOWN:
			if (cur == "-d") s = DICT;
			else if (cur == "-p") s = PLAYERS;
			else if (cur == "-t") s = TILEDEF;
			else return false;
			break;

		case DICT: //Handles "-d"
			if (dInput) return false;
			dict_filename = cur;
			s = UNKNOWN;
			dInput = true;
			break;

		case PLAYERS: //Handles "-p"
			
			//this will only happen if no first player name is given
			if (cur[0] == '-') return false;
			//Check to make sure no repeat names
			p = Player(cur);
			if (find(pnames.begin(), pnames.end(), p) != pnames.end()) return false;
			
			pnames.push_back(p);
			pInput = true;
			//If this is the last name, go to unknown state
			if (i+1 < argc) {
				next = argv[i+1];
				if (next[0] == '-') s = UNKNOWN;
			}
			break;

		case TILEDEF: //Handles "-t"
			if (tdInput) return false;
			tiledef_filename = cur;
			s = UNKNOWN;
			tdInput = true;
			break;
		}
	}
	
	//Return true if we have gotten a dictionary and a player name
	return true;
}

//Stores words from dictionary into the vector passed as argument "result"
//Returns 2 if unsuccessful in opening file, 4 if improper file
int read_dict(vector<string> & result, const char * dict)
{
	ifstream ifs (dict);
	if (ifs.is_open())
	{
		string temp;

		//Reads in words from dictionary file and pushes them on to result string.
		while (ifs >> temp)
		{
			if (temp.substr(0, 1) != "//")
			{
				transform(temp.begin(), temp.end(),temp.begin(), ::tolower);
				result.push_back(temp);
			}
		}

		return SUCCESS;

	} else {
		//Returns 2 if unable to open dictionary file
		cout << "Error in opening dictionary file in read_dict: " << dict << endl;
		return READ_DICT_ERR;
	}
}


//Generates vector of Letter Tile definitions from vector of strings
// First concatenates input vector into one long string, then sorts the
//vector by character.  Then counts how many times each letter occurs
//and creates a corresponding LetterTileDef.  Finally, it assigns a score
//to each letter tile def based on it's number of occurences.
int gen_tile_defs(const vector<string> & input, vector<LetterTileDef> & tiledefs)
{
	//Concatenate vector of strings
	string intermed = "";
	for (unsigned int i = 0; i < input.size(); i++)
	{
		intermed += input[i];
	}

	//Sort resulting string in ascending order
	sort (intermed.begin(), intermed.end());



	//Creates tile definitions with counts corresponding to the
	//number of occurences in the long string.
	int curIndex = -1;
	char matchLet = 0;
	char curLet;
	for (unsigned int i = 0; i < intermed.size(); i++)
	{
		curLet = intermed[i];
		if (intermed[i] == matchLet)
		{
			//Increment the last tile definitions count if this
			//character matches the previous one in the string
			++tiledefs[curIndex].count;
		} else {
			//Otherwise create a new letter tile and tile
			//definition with this letter and count of 1
			LetterTile curTile = LetterTile(curLet,0);
			LetterTileDef curDef = LetterTileDef(curTile,1);
			tiledefs.push_back(curDef);
			matchLet = curLet;
			++curIndex;
		}
	}

	//sort tiledefs in ascending order based on count
	//Note: This is where the operator< that was
	//overloaded in the LetterTileDef definition
	//comes into play.
	sort(tiledefs.begin(), tiledefs.end());


	//Assign scores based on count.  Tiles with the same
	//count get the same score.
	unsigned int numtiles = tiledefs.size();

	//Iterates over tiledefs in reverse adding one to the score
	//each time the count of the letter goes down meaning letters
	//with smaller counts have higher scores.	
	unsigned int curCount = tiledefs.back().count;
	unsigned int curScore = 1;
	for (vector<LetterTileDef>::reverse_iterator it = tiledefs.rbegin(); it < tiledefs.rend(); ++it)
	{
		if (it->count != curCount) {
			curCount = it->count;
			curScore++;
		}
		it->tile.score = curScore;
	}

	return SUCCESS;
}

//Takes in vector of LetterTileDefs and an optional filename.  For each
//letter tile defintion, writes a separate line with the letter, score,
// and count for that tile definition separated by a space.
int write_tile_defs(const vector<LetterTileDef> tiledefs, const char * filename) {
	ofstream ofs (filename);
	if (ofs.is_open()) {
		for (unsigned int i = 0; i < tiledefs.size(); ++i)
		{
			ofs << tiledefs[i].tile.letter << " " << tiledefs[i].tile.score << " " << tiledefs[i].count << endl;
		}
		ofs.close();
		return SUCCESS;
	} else {
		cout << "Error when trying to write tile defs to file" << endl;
		return WRITE_TD_ERR;
	}
}
