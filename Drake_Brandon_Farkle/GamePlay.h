#pragma once

//Includes
#include <vector>
#include <array>
#include "Player.h"

class GamePlay
{
private:
	
	//Validate Input
	int ValidateNumPlayers();

	//Messages
	void WelcomePlayers();
	void DisplayRules();
	void Farkle();
	void TurnTotal(int roundScore);
	void FinalRound(Player& player);
	void GameWinner(vector<Player>& players, Player& currentWinningPlayer);
	void EndOfTurnScores(vector<Player> players);

	//Create Players
	void SetPlayerNames(vector<Player>& players);

	//Check for scores and winner
	bool CheckWinningScore(Player& player);
	Player GetWinner(vector<Player>& players, Player& firstWinningPlayer);
	
	//Handle Dice
	void RollDice(vector<int>& dice);
	void ShowDiceRoll(vector<int>& diceRoll);
	bool IsScoringRoll(array<int, 6>& diceCount);
	int ScoreRoll(vector<int>& keptDice);
	array<int, 6> RollValueCount(vector<int>& diceRoll);
	vector<int> KeptDice(array<int, 6>& rollCount, vector<int>& keptDice);
	vector<int> reRollDice(int remainingDice);
	int SixKeptDiceReRoll(int &roundScore, std::vector<int> &keptDice, std::vector<int> &diceRoll, std::array<int, 6U> &rollValueCount, Player & player, bool &playerPass, int &retflag);
	void RollRemainingDice(std::vector<int> &reRoll, int keptDiceCount, std::array<int, 6U> &rollValueCount, bool &playerPass, int &roundScore, std::vector<int> &keptDice, int &retflag);

	//Round Logic
	int PlayerTurn(Player& player);

	

public:
	//Game
	void PlayGame();

};

