// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <vector>

using namespace std;


struct Position
{
	int row, col; // position of a cube (top letter) on the board
};

void showPath(const vector<Position>& path, ostream& os); //display vector path

#endif