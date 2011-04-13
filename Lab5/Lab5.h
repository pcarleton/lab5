// Lab5.h 
//
// Authors: Paul Carleton, Brian Fink, Stanford Rosenthal
//
// Purpose: the command line interface for the game

#ifndef LAB_5
#define LAB_5
#include "LetterTileDef.h"
#include <vector>
#include <string>

using namespace std;

int usage(char *);

//Helper functions for checking if the arguments are valid
bool checkArgs(int, char* argv[], string &, string &);
bool isD(char*);
bool isT(char*);

//Methods to generate tile defs file if the filename specified doesn't exist
int read_dict(vector<string> &, const char *);
int gen_tile_defs(const vector<string> &, vector<LetterTileDef> &);
int write_tile_defs(const vector<LetterTileDef>, const char * filename = "tile_defs.txt");

enum direction {VERTICAL, HORIZONTAL};

//Constants for return values from functions.
const int SUCCESS = 0;
const int IMPROPER_ARGS = 1;
const int  READ_DICT_ERR = 2;
const int INVALID_FILENAME_ERR  = 3;
const int READ_TILEDEF_ERR = 4;
const int TILEDEF_FORMAT_ERR = 5;
const int WRITE_TD_ERR = 6;
const int ERROR = -1;

#endif