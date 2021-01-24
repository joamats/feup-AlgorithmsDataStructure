// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#include <stdexcept>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include "Console.h"
#include "Configurations.h"
#include "Dictionary.h"
#include "Player.h"
#include "Board.h"
#include "Cube.h"
#include "gameReport.h"	

using namespace std;

int main() {
	setcolor(7, 0);
	unsigned int gameNumber = gameCounter(); // count number of games played
	ofstream reportStream = gameReportCreate(gameNumber);	// create .txt file for report

	srand((unsigned)time(NULL));

	// [1] Read Game Configurations ----------------------------------------------------------------------

	Configurations config;

	//Block that handles exceptions: aborts the program and displays error message
	try {
		config = readConfigurations("BOGGLE_CONFIG.txt");
	}
	catch (const string error_msg) {
		cerr << error_msg << endl; //shows error message
		return 1; //main ends with exit code 1
	}

	displayConfigurations(config, cout);
	displayConfigurations(config, reportStream); // for game Report

	// [2] Read Players ----------------------------------------------------------------------------------
	vector<Player> players = Player::collectPlayers(); // Collect all the players data

	for (auto& p : players) { 	// Display initial scores
		p.displayPlayersScores(cout);
		p.displayPlayersScores(reportStream);
	}

	bool foundWinner = false;

	try {
		// [3] Prepare Game ----------------------------------------------------------------------------------

		// Create Board
		Board board(config.boardFile);

		// Load dictionary
		Dictionary dic(config.dictionaryFile);

		int winnerIndex = 0;	// Create an index to save the winner position in the vector players
		unsigned int round = 0; // Counter of rounds
		bool play = board.newRound(cout, reportStream, round); // Ask if new round 

		// [4] Play Game! ------------------------------------------------------------------------------------
		while (!foundWinner && play) {

			round++;

			for (auto& t : players) {	// Read bets of each player
				board.display(cout);
				t.startPlay();			// Ask to press ENTER before start
				t.readWordsTimed(config.gameDuration, cout);
			}

			board.display(cout);		// For clear screen and display of board
			cout << endl << "Round " << round << " RESULTS: " << endl;

			for (auto& t : players)
				t.verifyBets(dic, board, cout, reportStream, config);

			for (auto& t : players) {	// Display Table of Scores
				t.displayPlayersScores(cout);
				t.displayPlayersScores(reportStream);
			}

			foundWinner = Player::findWinner(config.minPointsToWin, cout, winnerIndex, players); // Update if winner was found

			if (foundWinner)
				play = false; //only asks to play another round if the winner not found
			else
				play = board.newRound(cout, reportStream, round);	// if no winner, ask for a new round

		}

		if (foundWinner) {
			players.at(winnerIndex).displayWinner(cout); //display winners name and final score
			players.at(winnerIndex).displayWinner(reportStream);
		}
		else {
			for (auto& t : players)
				t.displayPlayersScores(cout);
		}

		gameReportClose(reportStream);

		return 0;
	}

	catch (const string error_msg) {
		cerr << error_msg << endl; //shows error message
		return 1; //main ends with exit code 1
	}

}

