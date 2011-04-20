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