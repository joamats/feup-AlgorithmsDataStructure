// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#include <ctime>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Console.h"
#include "Board.h"
#include "Position.h"
#include "Cube.h"

using namespace std;

Board::Board(const string& filename) {	// load and construct board from 'filename'

	readSize(filename, _numRows, _numCols);
	vector<string> allLetters = readChars(filename, _numRows, _numCols); // vector with all Letters is read

	for (size_t nrows = 0; nrows < _numRows; nrows++) {

		vector <Cube> boardRow;

		for (size_t ncols = 0; ncols < _numCols; ncols++) {
			vector<char> letters(allLetters.at(0).begin(), allLetters.at(0).end()); // vector<char> with, one at a time, each group of letters in the 1st line
			Cube c(letters); // construct the cube 
			allLetters.erase(allLetters.begin()); // erase the first line once it has been used
			boardRow.push_back(c); //add cube to board row
		}
		_board.push_back(boardRow);
	}
	cout << endl << "Board " << _numRows << 'x' << _numCols << " loaded with success." << endl;
}

char Board::getTopLetter(const Position& pos) const	{	// get top letter at position 'pos'
	return (_board.at(pos.row).at(pos.col).getTopLetter());
}

void Board::shuffle() {	// roll all cubes and shuffle them on the board
	for (size_t nrows = 0; nrows < _numRows; nrows++) {		// roll all dices
		for (size_t ncols = 0; ncols < _numCols; ncols++)
			_board.at(ncols).at(nrows).roll();
	}

	vector<Cube> auxBoard;									// shuffle all dices
	for (int rows = 0; rows < _numRows; rows++)
	{
		for (int cols = 0; cols < _numCols; cols++)			// reshape to 1d vector
			auxBoard.push_back(_board.at(rows).at(cols));
	}

	random_shuffle(auxBoard.begin(), auxBoard.end());		// shuffle all elements

	for (int rows = 0; rows < _numRows; rows++)
	{
		for (int cols = 0; cols < _numCols; cols++)			// reshape to 2d vector
			_board.at(rows % _numRows).at(cols % _numCols) = auxBoard.at(rows * _numCols + cols);
	}
}

void Board::display(ostream& os) const {	// display board
	clrscr();
	setcolor(4,8);
	os << "  ";
	for (size_t i = 0; i < _numCols; i++) { //set the number of cols
		// setcolor(7, 0);
		os << setw(3) << i + 1;
	}
	os << endl;
	for (size_t ncols = 0; ncols < _numCols; ncols++) {
		setcolor(4,8);
		os << setw(2) << right << ncols + 1; //set the number of rows
		setcolor(7, 0);
		for (size_t nrows = 0; nrows < _numRows; nrows++) {
			os << setw(3);
			_board.at(ncols).at(nrows).displayTop(os); //display each letter of board
		}
		os << endl;
	}
	setcolor(7, 0);
}

bool Board::findWord(string word, vector<Position>& path) {	// find 'word' on board

	vector<vector<bool>> visited(_numRows, vector<bool>(_numCols, false)); // Mark all characters as not visited 
	string str = ""; // Initialize test word 

	// Consider every character and look for 'word', starting with this character
	int numIter = 0;
	bool found = false;
	for (int i = 0; i < _numRows; i++)
	{
		for (int j = 0; j < _numCols; j++)
		{
			if (_board.at(i).at(j).getTopLetter() == word.at(0)) // find the first letter of word in the board
				findWordAux(visited, i, j, path, str, word, found);
			if (found) 
				return found; //leave the function when the word is found
		}
	}
	return found;
}

bool Board::newRound(ostream& os, ostream& osRep, unsigned int& round) { //ask the players if they want to continue or quit the game

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	// ignore exactly the number of characters in buffer

	cout << endl << "Press ENTER to roll the dices and start a new round, or 'Q' to quit the game ";
	
	if (cin.peek() != 'Q') {
		shuffle();
		osRep << "ROUND " << round + 1 << endl << endl;
		display(osRep);
		display(os);
		return true;
	}
	else
		return false;

}

bool Board::findWordAux(vector<vector<bool>>& visited, int i, int j, vector <Position>& path, string& str, const string& word, bool& found) //return true if path of word is found
{
	// Mark current board cell as visited and append current character to 'str'
	visited.at(i).at(j) = true;
	str = str + _board.at(i).at(j).getTopLetter();

	//Add to path the position of the letter
	Position letter_position;
	letter_position.row = i;
	letter_position.col = j;
	path.push_back(letter_position);

	// If 'str' is equal to 'word', then "announce" it has been found
	if (str == word)
	{
		found = true;
	}
	else
	{
		// Visit 8 adjacent cells of board[i][j] 
		for (int row = i - 1; row <= i + 1 && row < _numRows; row++)
			for (int col = j - 1; col <= j + 1 && col < _numCols; col++)
				if (row >= 0 && col >= 0 && !visited.at(row).at(col) && str.length() < word.length() && !found && word.substr(0, str.length()) == str)
					findWordAux(visited, row, col, path, str, word, found);

		// Erase current character from string, 
		// remove character position from 'path' and
		// mark visited[i][j] as false
		if (!found)
		{
			str.erase(str.length() - 1);
			path.pop_back();
			visited.at(i).at(j) = false;

		}
	}
	return found;
}

void Board::readSize(const string& filename, int& _numRows, int& _numCols) { //read size of board from file
	ifstream BoardFile;
	BoardFile.open(filename); //opens file

	if (BoardFile.fail()) { //if file doesn't open correctly
		string error_opening = "ERROR opening the Board File";
		throw error_opening;
	}
	string firstline;
	getline(BoardFile, firstline); //Getting first line of file, where size is
	stringstream FirstLine;
	FirstLine << firstline;
	char c1;
	string s1;

	if (!(FirstLine >> s1 >> _numCols >> c1 >> _numRows)) { //if information is not read correctly
		string error_reading = "ERROR: Board File not read correctly, please check if it has the right configuration.";
		throw error_reading;
	}
	BoardFile.close(); //close file
}

vector<string> Board::readChars(const string& filename, int& _numRows, int& _numCols) { //read letters from board
	vector<string> allLetters;

	ifstream BoardFile;
	BoardFile.open(filename); //opens file
	string line;

	while (getline(BoardFile, line)) {
		istringstream l(line);
		char c1, c2, c3, c4, c5, c6;
		l >> c1 >> c2 >> c3 >> c4 >> c5 >> c6;
		string letters = { c1,c2,c3,c4,c5,c6 };
		allLetters.push_back(letters);
	}

	allLetters.erase(allLetters.begin());

	BoardFile.open(filename); //close file

	return allLetters;
}