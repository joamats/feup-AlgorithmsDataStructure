// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

class Dictionary
{
public:
	Dictionary(const string& filename); // load "dictionary" from 'filename'
	bool find(const string& word); // find 'word' in "dictionary"

private:
	set<string> dictionary; // set with the dictionary
	void wordToUpper(string& word); // transform word in WORD
	
};

#endif
