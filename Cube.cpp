// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#include "Cube.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <cstddef>
#include <cstdlib>

using namespace std;

Cube::Cube(const vector<char>& letters){ // build a cube with 'letters' on faces 
	_letters = letters; //the faces of the cube are each letter of the vector letters
	_topSide = 0; //default topside is letters of index 0
}

void Cube::roll(){ // roll cube and change _topSide 
	_topSide = rand() % 6; //topside is random number between 0 and 5
}

char Cube::getTopLetter() const { // get top letter
	return _letters.at(_topSide); 
}

void Cube::displayTop(std::ostream& os) const { // display top letter
	os << getTopLetter();
}