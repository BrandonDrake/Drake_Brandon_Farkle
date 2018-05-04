#include "stdafx.h"
#include "Player.h"
//#include <string>
//#include <iostream>

using std::string;
using std::cout;
using std::cin;



Player::Player(string name)
{
	playerName = name;
}


Player::~Player()
{
}

string Player::getName() 
{
	return playerName;
}

void Player::setTotalScore(int turnScore)
{
	totalScore += turnScore;
}

int Player::getTotalScore() 
{
	return totalScore;
}
