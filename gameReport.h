// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#ifndef GAMEREPORT_H
#define GAMEREPORT_H

#include "Configurations.h"
#include "Dictionary.h"
#include "Player.h"
#include "Board.h"
#include "Cube.h"
#include <fstream>


using namespace std;

ofstream gameReportCreate(unsigned int& gameNumber); // create game Report file
void gameReportClose(ofstream& ofs); // close game Report file
unsigned int gameCounter(); //open or create file to increment number of games
bool fileExists(const string& filename); //check if file for game Counter exists

#endif