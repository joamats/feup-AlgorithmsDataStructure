// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Configurations
{
	string boardFile;
	string dictionaryFile;
	unsigned int gameDuration = 0; 
	unsigned int minLetters = 0;
	unsigned int minPointsToWin = 0;
};

Configurations readConfigurations(const string& configFileName); //read all configurations from file

string readConfigAux(ifstream& configFile, const string& configToRead); //read values from configurations file

void displayConfigurations(Configurations& config, ostream& os); //display game configurations

#endif