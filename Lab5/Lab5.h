// Lab5.h 
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
// Purpose: the command line interface for the game

#ifndef LAB_5
#define LAB_5
#include <vector>
#include <string>
#include "Constants.h"
#include "LetterTile.h"
#include "LetterTileDef.h"
#include "LetterTileCollection.h"
#include "Dictionary.h"
#include "GameBoard.h"
#include "Player.h"
#include "PlayOptions.h"

using namespace std;

int usage(char *);

//Helper functions for checking if the arguments are valid
bool checkArgs(int, char* argv[], string &, string &, vector<Player *> &);
bool isD(char*);
bool isT(char*);



//Methods to generate tile defs file if the filename specified doesn't exist
int read_dict(vector<string> &, const char *);
int gen_tile_defs(const vector<string> &, vector<LetterTileDef> &);
int write_tile_defs(const vector<LetterTileDef>, const char * filename = "tile_defs.txt");
int runFiles(string &, string&);




#endif