// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <vector>
#include <cstring>
#include <cstddef>

class Cube
{
public:
	Cube(const std::vector<char>& letters); // build a cube with 'letters' on faces 
	void roll(); // roll cube and change _topSide 
	char getTopLetter() const; // get top letter 
	void displayTop(std::ostream& os) const; // display top letter

private:
	std::vector<char> _letters; // the letters  of the cube
	std::size_t _topSide; // the side up: from 0 to 5
};

#endif