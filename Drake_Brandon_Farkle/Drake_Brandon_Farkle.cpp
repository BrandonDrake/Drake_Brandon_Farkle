// Drake_Brandon_Farkle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>
#include "GamePlay.h"




int main()
{
	//Seed Random Number Generator
	srand(time(NULL));
	
	GamePlay game; //Create game object

	game.PlayGame(); //Start the game

    return 0;
}

