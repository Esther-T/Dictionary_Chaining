//username: ltan
//authors: Adam Pesch and Esther Tan
//file name:client.cpp
// tests the operations of dictionary.cpp
// filename client.cpp
// date September 30, 2018

#include "dictionary.h"
#include <iostream>
#include <fstream>

using namespace std;

void readItemsWithDistinctAddresses(istream& input, Dictionary& myDictionary);
void readItemsAllHashingToTheSameAddress(istream& input, Dictionary& myDictionary);
void searchMeaningOfTwoTextingAbbrev(istream& input, Dictionary& myDictionary, Key& brb, Key& yil, Item& anItem, bool& isFound);
void removeSecondTextingAbbrev(istream& input, Dictionary& myDictionary, Key& deleteTest, bool& isFound, bool& isEmpty);
void searchMeaningOfFirstTextingAbbrev(istream& input, Dictionary& myDictionary, Key& yil, Item& anItem, bool& isFound);

int main()
{
	Item a, anItem;
	Key brb("brb");
	Key liy("liy");
	Key deleteTest("yli");
	bool isFull, isAlreadyThere, isFound, isEmpty;
	ifstream input;
	Dictionary myDictionary;
	
	input.open("in.dat");
	
	readItemsWithDistinctAddresses(input, myDictionary);
	
	readItemsAllHashingToTheSameAddress(input, myDictionary);
	
	searchMeaningOfTwoTextingAbbrev(input, myDictionary, brb, liy, anItem, isFound);
	
	removeSecondTextingAbbrev(input, myDictionary, deleteTest, isFound, isEmpty);
	
	searchMeaningOfFirstTextingAbbrev(input, myDictionary, liy, anItem, isFound);
	
	input.close();
	
	return 0;
}


void readItemsWithDistinctAddresses(istream& input, Dictionary& myDictionary)
{
	cout << "part 3a)" << endl;
	//part 3a input 4 unique abbreviations
	input >> myDictionary;
	
	cout << myDictionary << endl;
}

void readItemsAllHashingToTheSameAddress(istream& input, Dictionary& myDictionary)
{
	cout << "part 3b)" << endl;
	//part 3b input 3 more abbreviations that will out to the same spot as one of the previous ones
	input >> myDictionary;
	
	cout << myDictionary << endl;
}

void searchMeaningOfTwoTextingAbbrev(istream& input, Dictionary& myDictionary, Key& brb, Key& liy, Item& anItem, bool& isFound)
{
	cout << "part 3c)" << endl;
	//part 3c read 2 more abbreviations and look for their meanings. One is one of the original ones, one is the last one from part b
	cout << "currently searching for brb and liy" << endl << endl;
	
	myDictionary.searchForMeaning(brb, anItem, isFound);
	
	cout << anItem << endl << endl;
	
	myDictionary.searchForMeaning(liy, anItem, isFound);
	
	cout << anItem << endl << endl;
}

void removeSecondTextingAbbrev(istream& input, Dictionary& myDictionary, Key& deleteTest, bool& isFound, bool& isEmpty)
{
	cout << "part 3d)" << endl;
	//part 3d read another abbreviation that is the second from part b) and delete it
	myDictionary.deleteEntry(deleteTest, isEmpty, isFound);
	
	cout << "currently removing yli" << endl << endl;
	
	cout << myDictionary << endl;
}

void searchMeaningOfFirstTextingAbbrev(istream& input, Dictionary& myDictionary, Key& liy, Item& anItem, bool& isFound)
{
	cout << "part 3e)" << endl;
	//read and search for the last one from part b again, which makes you go by the deleted one
	cout << "currently searching for liy" << endl << endl;
	
	myDictionary.searchForMeaning(liy, anItem, isFound);
	
	cout << anItem << endl << endl;
}