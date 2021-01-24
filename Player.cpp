// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#include "Player.h"
#include "Configurations.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <algorithm>
#include "Dictionary.h"
#include "Board.h"
#include "Position.h"

using namespace std;

unsigned int Player::numPlayers = 0; // static int, counts number of Players created
vector<string> Player::roundBets = {}; //static vector, joins all the bets of each player, in a round
vector<int> Player::allScores = {}; //static vector, joins all the scores of each player, in a round

Player::Player() {	// class Constructor
	numPlayers++;	// update the number of players
	playerNumber = numPlayers; // each object's number will be the total number of Players in the moment
	name = "NO NAME ";	// default name
	bets = {};
	score = 0;
}

void Player::readInfo() {	// read Player's name, age would be useless

	if (playerNumber == 1)
		cout << "--- PLAYERS NAMES (till CTRL-Z) --" << endl;
	cout << "PLAYER " << playerNumber << ": ";
	getline(cin, name);
}

void Player::readWordsTimed(const unsigned int& duration, ostream& os) {	// read words of the player's bet, in one round (adapted from JAS - 2019/11/25)
	const char BEEP = (char)7;
	time_t t1 = time(NULL), t2;
	int tAvail;
	t2 = time(NULL);
	tAvail = (int)(duration - (t2 - t1));
	bets = {}; //clear bets for new round

	os << endl << "Word (available time: " << setw(2) << tAvail << "s): ";
	while (tAvail > 0)
	{
		string str;
		readStrTimed(str, tAvail);
		if (str != "" && !findRepetition(str, bets)) {
			bets.push_back(str); //add word to bets of player
			roundBets.push_back(str); //add each word to a vector with all the words betted
		}
		t2 = time(NULL);
		tAvail = (int)(duration - (t2 - t1));
		if (tAvail > 0)
			os << "Word (available time: " << setw(2) << tAvail << "s): ";
		else
			os << endl << "Time is over!" << BEEP << endl;
	}

}

void Player::displayPlayersScores(ostream& os) const {	// show table of scores
	if (playerNumber == 1) {
		os << endl << endl << "-------- TABLE OF SCORES ---------";// header if 1st player
		os << endl << setw(6) << right << "PLAYER" << "\t" << setw(18) << left << "NAME" << setw(7) << right << "SCORE" << endl;
	}
	os << setw(6) << right << playerNumber << "\t" << setw(18) << left << name << setw(7) << right << score << endl;
	if (playerNumber == numPlayers)
		os << endl;
}

void Player::verifyBets(Dictionary dic, Board bo, ostream& os_console, ostream& os_report, Configurations config) { //verify and display the score of each bet
	os_console << endl << name << "'s round results: " << endl;
	os_report << endl << name << "'s round results: " << endl;

	if (bets.empty()) //if the player didn't bet
	{
		os_console << endl << "No words to process"; 
		os_report << endl << "No words to process";
	}
	else {
		for (int b = 0; b < bets.size(); b++)
		{
			size_t word_size = bets.at(b).length(); //size of the word
			int word_score = 0; //the score of the word is, by default, 0
			os_console << endl << setw(15) << right << bets.at(b) << " | "; //display word
			os_report << endl << setw(15) << right << bets.at(b) << " | ";

			roundBets.erase(find(roundBets.begin(), roundBets.end(), bets.at(b))); //erase 1 time the word that we are analysing

			vector <Position> path;

			if (word_size < config.minLetters) //if the word has less than minimumletters
			{
				displayWordScore(word_score, os_console, " Word has not minimum letters");
				displayWordScore(word_score, os_report, " Word has not minimum letters");
			}
			else if (findRepetition(bets.at(b), roundBets)) //if the word was written by other players too
			{
				displayWordScore(word_score, os_console, " Word written by other players");
				displayWordScore(word_score, os_report, " Word written by other players");
			}
			else if (!(bo.findWord(bets.at(b), path))) //if the word can not be written in the board
			{
				displayWordScore(word_score, os_console, " Word cannot be written on the board");
				displayWordScore(word_score, os_report, " Word cannot be written on the board");
			}
			else if (!(dic.find(bets.at(b)))) //if the word is not found in the dictionary
			{
				displayWordScore(word_score, os_console, " Word not found in dictionary");
				displayWordScore(word_score, os_report, " Word not found in dictionary");
			}
			else //if the word is valid
			{
				switch (word_size) //display score of each word, according to it's size
				{
				case 3: case 4:
					word_score = 1;
					break;
				case 5:
					word_score = 2;
					break;
				case 6:
					word_score = 3;
					break;
				case 7:
					word_score = 5;
					break;
				default:
					word_score = 11;
				}
				score = score + word_score;
				displayWordScore(word_score, os_console, " Word is valid | ");
				displayWordScore(word_score, os_report, " Word is valid | ");
				showPath(path, os_console);
				showPath(path, os_report);
			}
			roundBets.push_back(bets.at(b)); //add the word initially removed 
		}
	}
	allScores.push_back(score); //vector with the total score of each player
	os_console << endl;
	os_report << endl;
}

void Player::displayWinner(ostream& os) const { //display winners info
	os << endl << "--------- THE WINNER IS ----------" << endl;
	os << name << ", WITH A SCORE OF " << score << " POINTS. " << endl;
}

vector<Player> Player::collectPlayers() { // loop to read several players' info
	vector <Player> players;
	bool anotherPlayer = true;

	while (anotherPlayer == true) {
		Player p;
		p.readInfo();
		players.push_back(p);

		if (cin.eof()) { //when CTRL-Z is typed
			players.erase(players.end() - 1);
			numPlayers--;
			anotherPlayer = false;
		}
	}
	return players;
}

void Player::startPlay() { //start to play the game
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	// ignore exactly the number of characters in buffer

	cout << endl << "Press ENTER to start " << name << "'s turn";
	cin.peek();

}

bool Player::findWinner(const int& minScore, ostream& os, int& winnerIndex, vector<Player>& players) { //return true if a player already reached the minimum score to win or if there is a tie

	int max = allScores.at(0);

	for (int p = 0; p < allScores.size(); p++) //find maximum value of players scores
	{
		if (allScores.at(p) > max) {
			max = allScores.at(p);
			winnerIndex = p; //send, by parameter, the index of the winner in the vector players
		}
	}

	allScores.erase(find(allScores.begin(), allScores.end(), max)); //erase the value of the highest score that appears first in the vector

	for (int p = 0; p < allScores.size(); p++) //find if there is any tie with the highest value of scores
	{
		if (allScores.at(p) == max) {
			allScores = {}; //restore the vector for next round 
			roundBets = {};
			return false;//if so, the players have to play another round
		}
	}
	if (max >= minScore) { //if the maximum score reaches the minimum number of points, the game stops 
		return true;
	}
	else {
		allScores = {}; //restore the vector for next round 
		roundBets = {};
		return false; //by default, return false
	}

}

void Player::readStrTimed(string& str, time_t duration) {	//Read a word to string 'str', before 'duration' time is elapsed, otherwise 'str' will be an empty string (JAS - 2019/11/25)
	const char CARRIAGE_RETURN = 13, SPACE = ' ', TAB = '\t', BACKSPACE = 8, BEEP = 7;
	str = ""; //str is empty
	time_t t1 = time(NULL), t2;
	int tAvail;
	t2 = time(NULL);
	tAvail = (int)(duration - (t2 - t1));

	while (tAvail > 0) {
		if (_kbhit()) {
			char c;
			c = _getch();
			c = toupper(c);
			if (c == SPACE || c == TAB || c == CARRIAGE_RETURN) {
				cout << endl;
				return;
			}
			else if (c == BACKSPACE) {
				str.pop_back();
				cout << "\b \b";
			}
			else
			{
				cout << c << flush;
				str = str + c;
			}
		}
		t2 = time(NULL);
		tAvail = (int)(duration - (t2 - t1));
	}
}

bool Player::findRepetition(const string& str, vector<string> _bets) { // check if word 'str' exists in vector _bets
	for (size_t i = 0; i < _bets.size(); i++) {
		if (_bets.at(i) == str)
			return true; //true if there is a string equal to str in the vector bets
	}
	return false; //by default, it assumes that the string str is not in the vector bets
}

void Player::displayWordScore(int& word_score, ostream& os, const string& cause){ //display score and cause for a word
	os << setw(7) << left << "SCORE: " << setw(2) << word_score << " | " << setw(8) << left << cause;
}
