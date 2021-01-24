// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Dictionary.h"
#include "Board.h"
#include "Configurations.h"


using namespace std;

class Player
{
public:
	Player();	// build a player with name = "NO NAME"

	void readInfo(); // read player's name
	void readWordsTimed(const unsigned int& duration, ostream& os); // read words of the player's bet, in one round
	void displayPlayersScores(ostream& os) const;  // show table of Scores
	void verifyBets(Dictionary dic, Board bo, ostream& os_console, ostream& os_report, Configurations config); //verify and display the score of each bet
	void displayWinner(ostream& os) const; //display winners info
	void startPlay(); //start to play the game
	int playerNumber;

	static vector<Player> collectPlayers(); // loop to read several players' info
	static bool findWinner(const int& minScore, ostream& os, int& winnerIndex, vector<Player>& players);
									//return true if a player already reached the minimum score to win
private:
	string name;
	vector<string> bets;
	int score; 

	static unsigned int numPlayers;
	static vector<string> roundBets;
	static vector<int> allScores;

	void readStrTimed(string& str, time_t duration);  //Read a word to string 'str', before 'duration' time is elapsed, otherwise 'str' will be an empty string

	bool findRepetition(const string& str, vector<string> _bets);	// check if word 'str' exists in vector _bets

	void displayWordScore(int& word_score, ostream& os,const string& cause); //display score and cause for a word
};

#endif