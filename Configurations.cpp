// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#include "Configurations.h"
#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

Configurations readConfigurations(const string& configFileName) { //read all configurations from file

	Configurations config; //declaring a struct of configurations

	ifstream configFile;
	configFile.open(configFileName); // open BOGGLE_CONFIG.txt
	if (configFile.fail()) //check if file opened correctly 
	{
		string error_opening = "ERROR opening the Configurations File";
		throw error_opening;
	}

	//Use readConfigAux to collect and save the data of each parameter on the file
	config.boardFile = readConfigAux(configFile, "Board filename .................... : ");
	config.dictionaryFile = readConfigAux(configFile, "Words filename .................... : ");
	config.gameDuration = stoi(readConfigAux(configFile, "Time per player bet (seconds) ..... : "));
	config.minLetters = stoi(readConfigAux(configFile, "Minimum number of letters in a word : "));
	config.minPointsToWin = stoi(readConfigAux(configFile, "Number of points needed to win ...  : "));

	configFile.close(); //close the file

	return config;
}

string readConfigAux(ifstream& configFile, const string& configToRead) { //read values from configurations file
	
	string line;

	while (getline(configFile, line)) {	// go through all lines of file until configToRead is found
		if (line.find(configToRead) != string::npos)
			return(line.erase(0, configToRead.length()));	// found string. Return configuration
	}

	string error_opening = "ERROR: Configurations File not read correctly, please check if it has the right configuration.";
	throw error_opening;

}

void displayConfigurations(Configurations& config, ostream& os) { //display game configurations
	os << "------ GAME CONFIGURATIONS -------" << endl;
	os << setw(21) << "Board File: " << config.boardFile << endl;
	os << setw(21) << "Dictionary File: " << config.dictionaryFile << endl;
	os << setw(21) << "Game Duration (s): " << config.gameDuration << endl;
	os << setw(21) << "Minimum of Letters: " << config.minLetters << endl;
	os << setw(21) << "Points to Win: " << config.minPointsToWin << endl;
	os << endl;
}
