#pragma once
#include <string>

using namespace std;

class Player
{
	
private:
	 int playerNumber;
	 int totalScore = 0;
	 bool inGameStatus = false;
	 bool isFirstWinner = false;

public:
	Player();
	Player(int);
	~Player();
	int getPlayerNumber(); 
	void setTotalScore(int);
	int getTotalScore();
	void setInGame();
	bool checkInGame();
	void FirstWinner();
	bool checkFirstWinner();
	
};

