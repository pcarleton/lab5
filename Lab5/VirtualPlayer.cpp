// Virtual Player.cpp
//
//  Defines methods for VirtualPlayer.cpp
//  
//


#include "stdafx.h"
#include "VirtualPlayer.h"
using namespace std;

VirtualPlayer::VirtualPlayer(string & n):Player(n),needNewTiles(false){
	//Player(n);
	//needNewTiles = false;
	cout << "VIRTUAL PLAYER CREATED" << endl;
}

int VirtualPlayer::getPlayChoice() {
	if (needNewTiles)
	{
		needNewTiles = false;
		return 1;
	}
	return 2;
}

PlayOptions VirtualPlayer::obtainPlayOptions(GameBoard & game) 
{
	//Constructs word collection with current tiles
	WordCollection wc(tileCollection, *game.getDict());
	

	//Attemps to play every combination of words these tiles make
	int maxScore = -1;
	PlayOptions playOps;
	for ( vector<LetterTileCollection>::iterator  iter = wc.getLTCS().begin();
			iter != wc.getLTCS().end(); ++iter)
	{
		tryPlay(*iter, playOps, maxScore, game);
	}
	if (maxScore <= 0) {
		needNewTiles = true;
		playOps.valid = false;
		return playOps;
	}
	LetterTileCollection curPlay;
	tileCollection.subCopy(playOps.tiles.as_string(), curPlay);
	playOps.tiles = curPlay;
	return playOps;

}

void VirtualPlayer::tryPlay(LetterTileCollection & ltc, PlayOptions & temp, int & maxScore, GameBoard & game) {

	//Attempts to play the specified tiles at every location in the board.
	int playScore = 0;
	for(int i = MIN_COORD; i <= MAX_COORD; ++i) {
		for(int j = MIN_COORD; j <= MAX_COORD; ++j) {
			playScore = game.play(ltc,make_pair(i,j), HORIZONTAL, true);
			if(playScore > 0 && playScore > maxScore) {
				maxScore = playScore;
				temp.coords = make_pair(i, j);
				temp.dir = HORIZONTAL;
				temp.tiles = ltc;
			}
			playScore = game.play(ltc,make_pair(i,j), VERTICAL, true);
			if(playScore > 0 && playScore > maxScore) {
				maxScore = playScore;
				temp.coords = make_pair(i, j);
				temp.dir = VERTICAL;
				temp.tiles = ltc;
			}
		}
	}
}