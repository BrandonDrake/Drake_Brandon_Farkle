#include "stdafx.h"
#include "rollDice.h"

#include <random>
#include <ctime>


rollDice::rollDice()
{
	srand(time(NULL));

	int roll[7];
	int numberCount[7] = {};

	for (int i = 1; i < 7; i++)
	{
		roll[i] = 1 + rand() % 6;
	}

	for (int r = 1; r < 7; r++)
	{
		cout << roll[r] << endl;
	}

	cout << endl;

	for (int i = 1; i < 7; i++)
	{
		numberCount[roll[i]]++;
	}

	for (size_t i = 1; i < 7; i++)
	{
		cout << numberCount[i] << endl;

	}


}


rollDice::~rollDice()
{
}
