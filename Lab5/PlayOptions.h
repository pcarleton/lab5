#ifndef PLAY_OPTIONS_H
#define PLAY_OPTIONS_H

#include "stdafx.h"
#include <iostream>
#include "Lab5.h"
using namespace std;

struct PlayOptions{
	pair<int,int> coords;
	direction dir;
	LetterTileCollection tiles;
};

#endif;