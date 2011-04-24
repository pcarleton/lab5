#include "stdafx.h"
#include "Player.h"
using namespace std;

Player::Player():name(""),score(0){
}
Player::Player(string & n):name(n),score(0){
}

bool Player::operator ==(const Player &other) const{
	return other.name == name;
}
int Player::numTiles(){
	return tileCollection.size();
}
void Player::receiveTiles(LetterTileCollection & bag, int n) {
	tileCollection.move(bag, n);
}
void Player::showTiles(ostream & os) {
	tileCollection.print(os);
}
int Player::getScore() {
	return score;
}
void Player::addScore(int s) {
	score += s;
}
int Player::checkString(string & input, LetterTileCollection & other) {
	return tileCollection.subCopy(input, other);
}
string Player::getName() {
	return name;
}