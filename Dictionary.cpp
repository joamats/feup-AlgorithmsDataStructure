// GRUPO 02
// João Matos
// Maria Loureiro
// Maria Carvalho

#include "Dictionary.h"
#include "Configurations.h"
#include <fstream>
#include <string>
#include <set>

using namespace std;

Dictionary::Dictionary(const string& filename) { // load "dictionary" from 'filename'

	ifstream dict;
	dict.open(filename);
	if (dict.fail()) { //if file doesn't open correctly
		string error_opening = "ERROR opening Dictionary File";
		throw error_opening;
	}
	string line;
	cout << endl << "Dictionary is loading ... " << endl; 
	while (getline(dict,line)){ //read each line of file
		wordToUpper(line); 
		dictionary.insert(line); //save word in dictionary
	}
	cout << "Dictionary loaded with success. " << endl; 
}
	
bool Dictionary::find(const string& word) { // find 'word' in "dictionary"
	string wordCapitals = word; // create WORD to keep const string& parameter - safety's sake
	wordToUpper(wordCapitals);
	return (dictionary.find(wordCapitals) != dictionary.end()); // true if found; false if not
}

void Dictionary::wordToUpper(string& word) { // transform word in WORD
	for (auto& c : word) // transforming every letter to CAPITAL
		c = toupper(c); 
}