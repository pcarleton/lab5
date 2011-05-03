// Player.cpp
//
// Brian, Stan, Paul
//
// Defines methods for Player class.


#include "stdafx.h"
#include "Player.h"
using namespace std;

Player::Player():name(""),score(0){
}
Player::Player(string & n):name(n),score(0){
}
// Two players are equal if their names are the same
bool Player::operator ==(const Player &other) const{
	return other.name == name;
}
// How many tiles does the Player have?
int Player::numTiles(){
	return tileCollection.size();
}
// Receive tiles from the bag
void Player::receiveTiles(LetterTileCollection & bag, int n) {
	tileCollection.move(bag, n);
}
// Print the tiles the Player has
void Player::showTiles(ostream & os) {
	tileCollection.print(os);
}
// Get the player's score
int Player::getScore() {
	return score;
}
// Compare the Players' scores
bool Player::operator <(const Player& other) const {
	return score < other.score;
}
void Player::addScore(int s) {
	score += s;
}
// Check the input against the tile collection
int Player::checkString(string & input, LetterTileCollection & other) {
	return tileCollection.subCopy(input, other);
}
//get the name
string Player::getName() {
	return name;
}
// Obtain the play choice
int Player::getPlayChoice() {
	cout << "~~~****Do you want to (1) Get New Tiles, (2) Make a Play, or (3) Quit? (1, 2, or 3) ******~~~~~" << endl;
	string input;
	cin >> input;
	return atoi(input.c_str());
}
LetterTileCollection & Player::getTileCollection() {
	return tileCollection;
}
// Obtain the play options. This includes the tiles to play,
// the coordinate of the play, and the direction of the play.
PlayOptions Player::obtainPlayOptions(GameBoard & game) {
	cout << "Enter what letters from your bag that you want to play." << endl;
	LetterTileCollection curPlay;
	PlayOptions playOps;
	//Loop until valid letter tiles selected
	while (true) {
		string input;
		cin >> input;
		if (checkString(input, curPlay) >= 0) {
			playOps.tiles = curPlay;
			break;
		}
		cout << "You don't have those tiles" << endl;
		showTiles(cout);
	}

	
	cout << "Enter the *start* coordinates of the *main* word:" << endl;
	
	//Loop until valid coords recieved
	int x = 0;
	int y = 0;
	while(true){
		cin >> x;
		cin.clear();
		cin.sync();
		cin >> y;
		cin.clear();
		cin.sync();
		pair<int,int> curCoords = make_pair(x, y);
		if (game.checkBounds(curCoords)) {
			playOps.coords = curCoords;
			break;
		}
		cout << "Invalid play, please enter 2 coordinates within the board." << endl;
	}

	cout << "Playing at : ( " << x << ", " << y << ")" << endl;
	

	//Loop until valid direction recieved
	string dirstr;
	direction dir;
	while (true) {
		cout << "Enter which direction to play (v for vert, h for horiz)" << endl;
		cin >> dirstr;
		
		if (dirstr == "v") {
			dir = VERTICAL;
			playOps.dir = dir;
			break;
		} else if (dirstr == "h"){
			dir = HORIZONTAL;
			playOps.dir = dir;
			break;
		} else {
			cout << "Please enter a v or h" << endl;
		}
	}
	playOps.valid = true;
	return playOps;
}