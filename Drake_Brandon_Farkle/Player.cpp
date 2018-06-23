#include "stdafx.h"
#include "Player.h"


Player::Player(){}

Player::Player(int number) //Constructor for each player
{
	playerNumber = number;
}


Player::~Player()
{
}

//Returns player
int Player::getPlayerNumber() 
{
	return playerNumber + 1; //Add one to the return value due to 0 indexed vectors
}

//Sets total score
void Player::setTotalScore(int turnScore)
{
	totalScore += turnScore; //Sets total score
}

//Return player's total score
int Player::getTotalScore() 
{
	return totalScore;
}

//Set in game status to true
void Player::setInGame()
{
	inGameStatus = true;
}

//returns in game status
bool Player::checkInGame()
{
	return inGameStatus;
}

//Identifies first player to score 10000 points
void Player::FirstWinner()
{
	isFirstWinner = true;
}

//returns whether player is first winner
bool Player::checkFirstWinner()
{
	return isFirstWinner;
}
