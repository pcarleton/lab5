#ifndef PLAY_OPTIONS_H
#define PLAY_OPTIONS_H

#include "stdafx.h"
#include <iostream>

using namespace std;

struct PlayOptions{
	pair<int,int> coords;
	direction dir;
	LetterTileCollection tiles;
};

#endif;