// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#ifndef BOARD_H
#define BOARD_H

#include "Dictionary.h"
#include "Cube.h"
#include "Position.h"

using namespace std;

class Board
{
public:
    Board(const string& filename); // load and construct board from 'filename'
    char getTopLetter(const Position& pos) const; // get top letter at position 'pos'
    void shuffle(); // roll all cubes and shuffle them on the board
    void display(ostream& os) const; // display board
    bool findWord(string word, vector<Position>& path); // find 'word' on board
                                                       // if 'word' is found, 'path' will contain the coordinates (lin,col) of the letters of the word
	bool newRound(ostream& os, ostream& osRep, unsigned int& round); //ask the players if they want to continue or quit the game

private:
    int _numRows, _numCols; // number of columns and number of rows of the board
    vector<vector<Cube>> _board; // board representation
    bool findWordAux(vector<vector<bool>>& visited, int i, int j, vector <Position>& path, string& str, const string& word, bool& found);
                                                                                                //return true if path of word is found
	void readSize(const string& filename, int& _numRows, int& _numCols); //read size of board from file
	vector<string> readChars(const string& filename, int& _numRows, int& _numCols); //read letters from board
};

#endif