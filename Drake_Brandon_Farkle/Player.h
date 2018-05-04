#pragma once
#include <string>

using namespace std;

class Player
{
	
private:
	 string playerName;
	 int totalScore = 0;

public:
	Player(string);
	~Player();
	string getName();
	void setTotalScore(int);
	int getTotalScore();
};

