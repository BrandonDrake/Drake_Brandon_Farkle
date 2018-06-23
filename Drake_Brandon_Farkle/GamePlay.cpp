#include "stdafx.h"
#include "GamePlay.h"
#include <random>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

#pragma region InputValidation
//Check user input for number of players
int GamePlay::ValidateNumPlayers()
{
	int userInput;
	cin >> userInput;

	while (true)
	{
		if (!cin) //If input fails, it is not a number. 
		{
			cout << "Invalid entry, please enter a number" << endl;
			cin.clear(); //Clear input
			cin.ignore(256, '\n'); //ignore rest of values
			cin >> userInput; //Ask for input again
		}
		else if (userInput < 2) //Ensures that there are more than 1 player
		{
			cout << "Please enter 2 or more players" << endl;
			cin.ignore(256, '\n');
			cin >> userInput;
		}
		else
		{
			return userInput;
		}
	}
}
#pragma endregion


#pragma region DisplayMessages
//Welcome Players and display rules
void GamePlay::WelcomePlayers()
{
	cout << "-------------------" << endl
		 << "STARTING NEW GAME" << endl
		 << "-------------------" << endl
		 << "How many players? (Must be 2 or more)";
}

//Display the rules
void GamePlay::DisplayRules()
{
	string line; //Variable to hold the read line
	string fileName = "FarkleRules.txt"; //Nameof file to be read
	ifstream readFile(fileName); //Opens File and assigns it to readFile

	if (readFile.is_open())
	{
		while (getline(readFile, line)) //Read the line in file and assign to line
		{
			cout << line << endl;
		}

		readFile.close();
	}
	else
	{
		cout << "Problem reading or opening the rules file" << endl;
	}
}

//Tell user if they rolled a Frakle
void GamePlay::Farkle()
{
	cout << endl << endl
		 << "--------------------------------" << endl
		 << "FARKLE!! Your turn has ended" << endl
		 << "--------------------------------" << endl << endl;

}

//Displays the total for the player's turn
void GamePlay::TurnTotal(int roundScore)
{
	cout << "\n ----------------------------" << endl
		 << "TURN SCORE: " << roundScore << endl << endl;
}

//Lets players know they have entered final round
void GamePlay::FinalRound(Player& player)
{
	cout << "***********************************************" << endl
		 << "Player " << player.getPlayerNumber()
		 << " has scored 10,000 points\n"
		 << "We have entered the FINAL ROUND of play\n"
		 << "Each player will have one more chance to roll "
		 << "to beat Player " << player.getPlayerNumber() << "'s score." << endl 
		 << "************************************************" << endl << endl;
}

//Displays the final winner
void GamePlay::GameWinner(vector<Player>& players, Player& currentWinningPlayer)
{
	Player finalWinner = 0;

	finalWinner = GetWinner(players, currentWinningPlayer);
	cout << "------------------------------" << endl
		 << "THE GAME HAS ENDED!!" << endl
		 << "-------------------------------" << endl << endl
		 << "**********************" << endl
		 << "GAME WINNER" << endl
		 << "**********************" << endl;

	cout << "PLAYER " << finalWinner.getPlayerNumber() << " !!!!!" << endl;
}

//Display scores for all players at end of each turn
void GamePlay::EndOfTurnScores(vector<Player> players)
{
	cout << endl << endl;
	cout << "********************" << endl
		 << "Total Scores" << endl
		 << "********************" << endl;

	for (size_t i = 0; i < players.size(); i++)
	{
		cout << "Player " << i + 1 << ": "
			 << players[i].getTotalScore() << endl;
	}
}
#pragma endregion


#pragma region PlayerSetup
//Create player objects
void GamePlay::SetPlayerNames(vector<Player>& players)
{
	system("cls"); //Clears away rules on game start

	cout << "Welcome Players" << endl;

	for (unsigned int i = 0; i < players.size(); i++)
	{
		players[i] = Player(i); //Create player objects from number of players entered
		cout << "Player " << players[i].getPlayerNumber() << endl; //Display player numbers
	}
}
#pragma endregion


#pragma region WinnerFunctions
//Check if player has a winning score
bool GamePlay::CheckWinningScore(Player& player)
{
	bool isAWinningScore = false;

	isAWinningScore = player.getTotalScore() >= 10000 ? true : false; //Check player score and rreturn bool

	return isAWinningScore;
}

//Determine the final the winner after final round of play is complete
Player GamePlay::GetWinner(vector<Player>& players, Player& firstWinningPlayer)
{
	Player finalWinner = firstWinningPlayer; //If none of other scores are higher, final winner is first winner

	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i].getTotalScore() > firstWinningPlayer.getTotalScore()) //compare score of remaining players against first winner
		{
			finalWinner = players[i]; //Set final winner
		}
	}

	return finalWinner;
}
#pragma endregion


#pragma region HandlingDice
//Rolling the dice
void GamePlay::RollDice(vector<int>& dice)
{
	//Roll dice and fill vector with rolls
	for (unsigned int i = 0; i < dice.size(); i++)
	{
		dice[i] = 1 + rand() % 6;
	}
}

//Display results fo the roll
void GamePlay::ShowDiceRoll(vector<int>& diceRoll)
{
	cout << "******************" << endl
		 << "Roll"				 << endl
		 << "******************" << endl;

	for (unsigned int i = 0; i < diceRoll.size(); i++)
	{
		cout << "Dice [" << i + 1 << "]: " << diceRoll[i] << endl;
	}
}

//Check to see if roll had scoring dice
bool GamePlay::IsScoringRoll(array<int, 6>& diceCount)
{
	if (diceCount[0] >= 1 || diceCount[4] >= 1) //Check for 1' and 5's
	{
		return true;
	}

	for (unsigned int i = 1; i < diceCount.size(); i++) // Check for 3 of a kind ignoring 1's and 5's(indexing starts at 1 to skip 1's) 
	{
		if (i == 4) { i = 5; } //Skips 4th index to ignore 5

		if (diceCount[i] >= 3)
		{
			return true;
		}
	}

	return false;
}

//Score the player's roll
int GamePlay::ScoreRoll(vector<int>& keptDice)
{
	int rollScore = 0;

	if (keptDice[0] < 3) // Have less than 3 1's only 100 each
	{
		rollScore += keptDice[0] * 100; 
	}
	if (keptDice[4] < 3) //Less than 3 5's only worth 50 each
	{
		rollScore += keptDice[4] * 50;
	}
	if (keptDice[0] >= 3) //3 or more 1's worth 1,000 points
	{
		rollScore += 1000;
	}

	for (unsigned int i = 1; i < keptDice.size(); i++) //start indexing at 1 to skip the 1's(handled above)
	{
		if (keptDice[i] >= 3) //check for 3 of a kind on other die values
		{
			rollScore += ((i + 1) * 100); //Points is die value * 100
		}
	}

	return rollScore;
}

//Determine number of times die value was rolled
array<int, 6> GamePlay::RollValueCount(vector<int>& diceRoll)
{
	array<int, 6> count = { 0 }; //Creates array to store the count

	//Get count on number of times a die is rolled
	for (unsigned int i = 0; i < diceRoll.size(); i++)
	{
		count[diceRoll[i] - 1]++; //Takes the value of the roll and subtracts one due to 0 indexing(otherwise get out of range exception)
	}

	return count;
}

//Vector of which scoring dice were kept
vector<int> GamePlay::KeptDice(array<int, 6>& rollCount, vector<int>& keptDice)
{
	//Check for 1's and 5's
	if (rollCount[0] >= 1)
	{
		keptDice[0] += rollCount[0]; //Add to vector
	}
	if (rollCount[4] >= 1 && rollCount[4] < 3)
	{
		keptDice[4] += rollCount[4]; //Add to vector
	}

	//Check for three of a kind
	for (unsigned int i = 1; i < rollCount.size(); i++)
	{
		if (rollCount[i] >= 3)
		{
			keptDice[i] += rollCount[i]; //Add to vector
		}

	}

	return keptDice;
}
#pragma endregion


#pragma region HandlingRerolls
//VS Auto function extraction for Rolling the remaining dice (Was in PlayerTurn function, but the function became too large)
void GamePlay::RollRemainingDice(vector<int> &reRoll, int keptDiceCount, array<int, 6U> &rollValueCount, bool &playerPass, int &roundScore, vector<int> &keptDice, int &retflag)
{
	retflag = 1;
	cout << "------------------------------------------------" << endl
		<< "You have chosen to Roll the remaining dice" << endl
		<< "------------------------------------------------" << endl;

	reRoll = reRollDice(6 - keptDiceCount); //Rerolls the dice to fill the remaining dice

	cout << "***************" << endl
		<< "Your  Re-Roll" << endl
		<< "****************" << endl;

	//Show dice on reroll
	ShowDiceRoll(reRoll);

	//Count the numbers rolled
	rollValueCount = RollValueCount(reRoll);

	//Check that player did not farkle
	if (!IsScoringRoll(rollValueCount))
	{
		Farkle();
		playerPass = true;
		roundScore = 0;
		{ retflag = 3; return; }; //Skip remaining code and advance directly to while condition 
	}
	else
	{
		keptDice = KeptDice(rollValueCount, keptDice); //Update the kept dice vector
		roundScore = ScoreRoll(keptDice); // Rescore the turn
	}
}

//Generates the die values for reroll
vector<int> GamePlay::reRollDice(int remainingDice)
{
	vector<int> reRoll(remainingDice); 

	for (int i = 0; i < remainingDice; i++) //Only rolls die based on number of dice left after being kept
	{
		reRoll[i] = 1 + rand() % 6;
	}

	return reRoll;
}

// VS auto function extraction Reroll all dice if all six are kept to record points (PlayerTurn function becoming too crowded)
int GamePlay::SixKeptDiceReRoll(int &roundScore, std::vector<int> &keptDice, std::vector<int> &diceRoll, std::array<int, 6U> &rollValueCount, Player & player, bool &playerPass, int &retflag)
{
	retflag = 1;

	cout << endl
		 << "--------------------------------------------------------" << endl
		 << "You must reroll and not Farkle to keep current points"	   <<endl
		 << "--------------------------------------------------------" << endl << endl;
	
	//Roll Dice again
	RollDice(diceRoll);
	ShowDiceRoll(diceRoll);
	
	//Check which numbers were rolled
	rollValueCount = RollValueCount(diceRoll);

	//Check if a scoring roll
	if (IsScoringRoll(rollValueCount) && player.checkInGame() == true) //Is a scoring roll and player is in game
	{
		cout << "\n You kept your points!!" << endl << endl;
		playerPass = true;
		return roundScore;
	}
	else if (IsScoringRoll(rollValueCount) && player.checkInGame() == false && roundScore >= 1000) // is a scoring roll and scored enough points to enter the game
	{
		playerPass = true;
		cout << "\n You have kept your points and you have entered the game!!" << endl << endl;
		player.setInGame();
		return roundScore;
	}
	else
	{
		if (!player.checkInGame()) //Roll is lower than 1,000 and player is not in game
		{
			cout << "You are not in the game, you must score at least 1,000 points" << endl;
		}
		else //Reroll did not produce any scoring dice
		{
			Farkle();
		}

		//Player must pass and score is 0
		playerPass = true;
		roundScore = 0;
		{ retflag = 3; return {}; };
	}
}
#pragma endregion



#pragma region GamePlay
//Function for each players turn
int GamePlay::PlayerTurn(Player& player)
{
	//Local Variables
	int roundScore = 0;				
	int keptDiceCount = 0;
	vector<int> diceRoll(6, 0);
	array<int, 6> rollValueCount;
	vector<int> keptDice(6, 0);
	vector<int> reRoll;

	bool farkle = false;
	bool playerPass = false;


	do 	//Loop for each player's turn
	{
		//Display Player info
		cout << endl << endl
			<< "-------------------" << endl
			<< "PLAYER "			 << player.getPlayerNumber() << "'s turn" << endl
			<< "IN GAME STATUS: "	 << boolalpha << player.checkInGame() << endl
			<< "-------------------" << endl << endl;

		//Roll and display the dice
		RollDice(diceRoll);
		ShowDiceRoll(diceRoll);

		//Count how many times each die value was rolled
		rollValueCount = RollValueCount(diceRoll);

		//Check that the roll has any scoring die
		if (!IsScoringRoll(rollValueCount))
		{
			Farkle(); //Display farkle message
			playerPass = true;
			continue; //Skip remaining code and advance directly to while condition 
		}

		//Determine which dice to keep
		keptDice = KeptDice(rollValueCount, keptDice);

		//Calculate the turn score
		roundScore = ScoreRoll(keptDice);

		//Check to see how many dice were kept
		for (unsigned int i = 0; i < keptDice.size(); i++)
		{
			keptDiceCount += keptDice[i];
		}

		//Check for ReRoll
		if (!player.checkInGame() && roundScore < 1000 && keptDiceCount <= 3)
		{
			int retflag; //local variable to determine whether player rolled farkle and to continue play

			//Call the function to Roll Remaining dice if conditions are met
			RollRemainingDice(reRoll, keptDiceCount, rollValueCount, playerPass, roundScore, keptDice, retflag);

			//If function returns 3, player farkled on reroll
			if (retflag == 3) continue;
		}

		//Check if all six dice are kept
		if (keptDiceCount == 6)
		{
			int retflag; //Holds result of function call

			//Call function if all six dice kept
			int retval = SixKeptDiceReRoll(roundScore, keptDice, diceRoll, rollValueCount, player, playerPass, retflag);

			//return value from function call
			if (retflag == 3) continue;

			roundScore = retval; //Sets return value to roundScore
		}

		//Check the In Game status of the player and whether they scored enough to enter the game or record score
		if (player.checkInGame() == false && roundScore < 1000) //If player not in game and scored less than 1000
		{
			cout << "\n You did not score enough points to enter the game this round. Maybe Next time" << endl << endl;
			playerPass = true;
			roundScore = 0;
			continue;
		}
		else if (player.checkInGame() == false && roundScore >= 1000) //Player is not in game and scored more than 1000
		{
			cout << "\n You have entered the game!!" << endl << endl;
			player.setInGame(); //Puts player in the game
			playerPass = true;
			continue;
		}
		else //Player is in the game and points are recorded
		{
			playerPass = true;
		}
	} while (!playerPass); //Continues while player has not passed 

	return roundScore;
}

//Overall Game Play
void GamePlay::PlayGame()
{
	//Local Variables
	int numPlayers = 0;
	int currentPlayer = 0;
	int roundScore = 0;
	bool winner = false;
	Player winningPlayer = 0;

	//Displays rules from .txt file
	DisplayRules();

	//Welcome and get the number of players
	WelcomePlayers();
	numPlayers = ValidateNumPlayers();

	//Create the player objects and set default names
	vector<Player> players(numPlayers);
	SetPlayerNames(players);

	//Loops through the gameplay until there is a winner and checks to see first winner to end final round
	while (!winner || !players[currentPlayer].checkFirstWinner())
	{
		//Reset roundScore
		roundScore = 0;

		//Begins the players turn
		roundScore = PlayerTurn(players[currentPlayer]);

		//Display and Set the Total score from the turn
		TurnTotal(roundScore);
		players[currentPlayer].setTotalScore(roundScore);
		
		//Display Player Scores
		EndOfTurnScores(players);

		//Check for winning score and that there is not already a winner
		if (!winner && CheckWinningScore(players[currentPlayer]))
		{
			winningPlayer = players[currentPlayer]; //Sets current player as winner
			players[currentPlayer].FirstWinner(); //Sets current player as first winner
			winner = true;
			FinalRound(players[currentPlayer]); //Display final round message
		}

		//Advance to next player
		currentPlayer++;

		//Check that current player returns to 0 once last player is reached
		if (currentPlayer == numPlayers)
		{
			currentPlayer = 0;
		}
	}

	//End of game 
	GameWinner(players, winningPlayer); //Retrieves the winner
	system("pause"); //Pause the system if run with debugger and keep console open
}
#pragma endregion



