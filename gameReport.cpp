// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#include "gameReport.h"
#include "Configurations.h"
#include "Dictionary.h"
#include "Player.h"
#include "Board.h"
#include "Cube.h"
#include <fstream>
#include <sstream>
#include <ios>
#include <iomanip>
#include <string>

using namespace std;

ofstream gameReportCreate(unsigned int& gameNumber) { // create game Report file
	ofstream ofs;
	ostringstream oss;
	oss << setw(3) << setfill('0') << gameNumber;
	string formattedNumber = oss.str();
	string reportName = "BOGGLE_GAME_" + formattedNumber + ".txt";
	ofs.open(reportName);
	ofs << "------ REPORT GAME NUMBER " << gameNumber << " ------" << endl << endl;
	return ofs;
}

void gameReportClose(ofstream& ofs) { // close game Report file
	ofs.close();
}

unsigned int gameCounter() { //open or create file to increment number of games
	unsigned int gameNumber;
	string file = "BOGGLE_GAME_NUM.txt";
	fstream fs;
	if (!fileExists(file)) {  // if file does not exist ... 
		fs.open(file, ios::out); //... create the file
		gameNumber = 0; //set number of games to 0
		fs << gameNumber;
		fs.close();
	}
	else {
		fs.open(file, ios::in);
		fs >> gameNumber;
		fs.close();

		fs.open(file, ios::out);
		gameNumber++;
		fs << gameNumber;
		fs.close();
	}

	return gameNumber;
}

bool fileExists(const string& filename) {	//check if file for game Counter exists
	ifstream ifile;
	ifile.open(filename);
	if (ifile.is_open()) {
		ifile.close();
		return true;
	}
	else
		return false;
}