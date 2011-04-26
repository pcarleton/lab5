#ifndef CONSTANTS
#define CONSTANTS

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
const int SPECIAL_CELLS_FORMAT_ERR = 7;
const int READ_SPECIAL_CELLS_ERR = 8;

#endif