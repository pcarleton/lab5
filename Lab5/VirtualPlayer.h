#ifndef VIRTUAL_PLAYER
#define VIRTUAL_PLAYER
#include "Player.h"
#include "Constants.h"
#include "WordCollection.h"

class VirtualPlayer: public Player {
public:
	VirtualPlayer(string &);
	virtual int getPlayChoice();
	virtual PlayOptions obtainPlayOptions(GameBoard &);
private:
	void tryPlay(LetterTileCollection &, PlayOptions &, int &, GameBoard &);
	bool needNewTiles;
};

#endif