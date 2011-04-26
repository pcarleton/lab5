#include "stdafx.h"
#include "VirtualPlayer.h"
using namespace std;

VirtualPlayer::VirtualPlayer(string & n):Player(n),needNewTiles(false){
	//Player(n);
	//needNewTiles = false;
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
	WordCollection wc(tileCollection, *game.getDict());
	//WARNING: Multi-lined for loop.
	int maxScore = -1;
	PlayOptions playOps;
	for ( vector<LetterTileCollection>::iterator  iter = wc.getLTCS().begin(); //continued on the next line
			iter != wc.getLTCS().end(); ++iter) //continued from previous line
	{
		tryPlay(*iter, playOps, maxScore, game);
	}
	if (maxScore <= 0) {
		needNewTiles = true;
		playOps.valid = false;
		return playOps;
	}
	return playOps;

}

void VirtualPlayer::tryPlay(LetterTileCollection ltc, PlayOptions & temp, int & maxScore, GameBoard & game) {
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