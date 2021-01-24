// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#include <iostream>
#include <vector>
#include "Position.h"

using namespace std;

void showPath(const vector<Position>& path, ostream& os) { //display vector path
	os << "PATH: ";
	for (size_t i = 0; i < path.size() - 1; i++)
		os << '(' << path.at(i).row + 1 << ',' << path.at(i).col + 1 << ") -> ";
	if (path.size() > 0)
		os << '(' << path.at(path.size() - 1).row + 1 << ',' << path.at(path.size() - 1).col + 1 << ')';
}
