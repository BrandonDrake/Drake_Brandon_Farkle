// Drake_Brandon_Farkle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int main()
{
	Player player1("Tom");
	Player player2("Tim");

	cout << player1.getName() << endl;
	player1.setTotalScore(34);
	cout << player1.getTotalScore() << endl;
	player1.setTotalScore(34);
	cout << player1.getTotalScore() << endl;
	cout << endl;
	cout << player2.getName() << endl;
	cout << player2.getTotalScore()<< endl;
	cout << endl;
	rollDice();

    return 0;
}

