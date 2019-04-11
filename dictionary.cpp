//username: ltan
// authors: Esther Tan
//file name: dictionary.cpp
// Implementation of ADT Dictionary
//     data object: a bunch of texting abbreviations and their meanings 
//     operations: create, destroy
//                 search the dictionary for an item given its text
//                 insert a new item into the dictionary
//                 remove an item from the dictionary given its text
//   associated operations: input and output
// filename dictionary.cpp
// date September 30, 2018

#include "dictionary.h"
#include "stack.h"
#include <iostream>

const int TABLESIZE = 11;

struct DictionaryRecord
{
	int numberOfItems;
	Stack* hashTablePtr;
};

// returns address of some texting abbreviation
// using function convert to integer and modding
// with size of dictionary hash table
// pre: myKey is a texting abbreviation, TABLESIZE is
//	    greater than or equal to zero
// post: returns address of myKey (texting abbreviation)
int hashFunction(const Key& myKey)
{
	return myKey.convertToInteger() % TABLESIZE;
}

// returns the modulus of integer and TABLESIZE
// pre: integer is assigned, TABLESIZE is
//	    greater than or equal to zero
// post: returns integer % TABLESIZE
int modTABLESIZE(const int& integer)
{
	return integer % TABLESIZE;
}

//prints the stack of the hashtableptr[i]
//pre:   Stack dictionaryPtr -> hashTablePtr[i] exists 
//post:  Stack dictionaryPtr -> hashTablePtr[i] is printed to the screen
//       in a reverse manner with its top item at the bottom and vice versa
//usage: printStack(dictionaryPtr -> yourStack[i]);
void printStack(Stack hashTablePtr)
{
	Item topItem;
	bool isAdded;
	if(hashTablePtr.isEmpty())
	{
		cout << endl;
	}
	while (!hashTablePtr.isEmpty())
	{
		hashTablePtr.getTop(topItem);
		cout << "\t" << topItem << endl;
		hashTablePtr.pop();
	}
}

//search the stack
//pre:   dictionaryPtr -> hashtableptr[i] stack exists and 
//       targetText and anItem are assigned
//       bool isFound is assigned
//post:  if topItem == targetText then anItem is topItem and isFound is true
//usage: searchStack(yourStack, targetText, anItem, isFound);
void searchStack(Stack tempCopy, const Key& targetText, Item& anItem, bool& isFound)
{
	Item topItem;
	tempCopy.getTop(topItem);
	isFound = (topItem == targetText);
	while(!isFound && !tempCopy.isEmpty())
	{
		tempCopy.pop();
		tempCopy.getTop(topItem);
		isFound = (topItem == targetText);
	}
	if (isFound)
	{
		tempCopy.getTop(topItem);
		anItem = topItem;
	}
}

// displays a dictionary
// pre: output has been opened if it is a file
//      rightHandSideDictionary has been assigned items
// post: output contains each item on a separate line in the format with headings.
//       for example
//       address    text       meaning
//          0        lol       laugh out loud
//          1        ttyl      talk to you later
// usage: outfile << myDictionary;
ostream& operator<< (ostream& output, const Dictionary& rightHandSideDictionary)
{
	output << "address\ttext\tmeaning" << endl;
	for (int i = 0 ; i < TABLESIZE; i++)
	{
		output << "   " << i;
		printStack(rightHandSideDictionary.dictionaryPtr -> hashTablePtr[i]);
	}
	return output;
}

// inputs items into a dictionary
// pre: input has been opened if it is a file
//      items are arranged in the following format
//      2
//      lol
//      laugh out loud
//      ttyl
//      talk to you later
// post: if there is room, 
//       all items in the input have been stored in rightHandSideDictionary
// usage: infile >> myDictionary;
istream& operator>> (istream& input, Dictionary& rightHandSideDictionary)
{
	bool isFull = false;
	bool isAlreadyThere = false;
	int numOfInputs;
	
	input >> numOfInputs;
	input.ignore();
	for (int i = 0; ((i < numOfInputs) && (!isFull)); i++)
	{
		Item anItem;
		input >> anItem;
		rightHandSideDictionary.addNewEntry(anItem, isFull, isAlreadyThere);
	}
	return input;
}

// creates a new dictionary
// post: Dictionary object exists but is empty
// usage: Dictionary myDictionary;	
Dictionary::Dictionary()
{
	dictionaryPtr = new DictionaryRecord;
	dictionaryPtr -> numberOfItems = 0; 
	dictionaryPtr -> hashTablePtr = new Stack[TABLESIZE];
}

// destroys a dictionary
// pre: Dictionary object exists
// post: all memory for Dictionary object has been freed
// usage: automatically done at the end of scope
Dictionary::~Dictionary()
{
	delete [] dictionaryPtr -> hashTablePtr;
	dictionaryPtr -> hashTablePtr = nullptr;
	delete dictionaryPtr;
	dictionaryPtr = nullptr;
}

// search for a meaning with a given text
// pre targetText has been assigned 
// post if an item with texting abbreviationthe same as targetText is found then
//       isFound is true and theItem is that item
//       else isFound is false
// usage  myDictionary.searchForMeaning(targetText, anItem, isFound);
void Dictionary::searchForMeaning(const Key& targetText, Item& anItem, bool& isFound)
{
	int address = (hashFunction(targetText));
	Stack tempCopy(dictionaryPtr -> hashTablePtr[address]);
	Item topItem;
	
	tempCopy.getTop(topItem);
	isFound = (topItem == targetText);

	int previousAddress = modTABLESIZE(address - 1);
	
	if (isFound)
	{
		tempCopy.getTop(topItem);
		anItem = topItem;
	}
	while (!isFound && previousAddress != address && !tempCopy.isEmpty())
	{
		address = modTABLESIZE(address + 1);
		tempCopy.getTop(topItem);
		isFound = (topItem == targetText);
		searchStack(tempCopy, targetText, anItem, isFound);
	}
}

//checks if newItem is already in Stack 
//pre:   dictionaryPtr -> hashTablePtr[address] stack exists
//       newItem is assigned and bool isAlreadyThere is assigned
//post:  if newItem = topItem, isAlreadyThere is true otherwise it is false
//usage: checkifisAlreadyThere(yourStack, newItem, isAlreadyThere)
void checkifisAlreadyThere(Stack tempCopy, const Item newItem, bool& isAlreadyThere)
{
	Item topItem;
	while (!tempCopy.isEmpty())
	{
		tempCopy.getTop(topItem);
		if (topItem == newItem)
		{
			isAlreadyThere = true;
		}
		else 
		{
			isAlreadyThere = false;
		}
		tempCopy.pop();
	}
}

// inserts a new text's item into the dictionary
// pre: newItem has been assigned
// post: if there is room in the Dictionary object and newItem's text
//            is not already there  isFull is false and isAlreadyThere is false
//            and newItem is appropriately added
//       else either isFull is true or isAlreadyThere is true, depending
// usage: myDictionary.addNewEntry(myItem, isFull, isAlreadyThere);
void Dictionary::addNewEntry(const Item& newItem, bool& isFull, bool& isAlreadyThere)
{
	bool isAdded;
	bool isFound = false;
	int address = hashFunction(newItem);
	int i = address;
	int indexStop = modTABLESIZE(address - 1);
    
	while (i != indexStop)
	{
		checkifisAlreadyThere(dictionaryPtr -> hashTablePtr[i], newItem, isAlreadyThere);
		i = modTABLESIZE(i + 1);
	}
	
	if (!isAlreadyThere && !isAdded)
	{
		dictionaryPtr -> hashTablePtr[address].push(newItem, isAdded);
		dictionaryPtr -> numberOfItems++;
	}
}

//deletes item from the stack
//pre:   dictionaryPtr -> hashTablePtr[i] stack exists and it is not empty
//       targetText is assigned and isFound is false
//post:  targetText and its meaning is deleted from stack and isFound is true
//usage: deleteFromStack(dictionaryPtr -> yourStack[i], targetText, isFound);
void deleteFromStack(Stack& hashTablePtr, const Key& targetText, bool& isFound)
{
	Stack tempStack;
	Item topItem;
	bool isAdded;
	
	while(!isFound && !hashTablePtr.isEmpty())
	{
		hashTablePtr.getTop(topItem);
		isFound = (targetText == topItem);
		if(!isFound)
		{
			tempStack.push(topItem, isAdded);
		}
		hashTablePtr.pop();
	}
	
	while(!tempStack.isEmpty())
	{
		tempStack.getTop(topItem);
		hashTablePtr.push(topItem, isAdded);
		tempStack.pop();
	}
}

// removes the item associated with a given text from the dictionary
// pre: targetText is assigned
// post: if Dictionary object is not empty and 
//           targetText is found in Dictionary object, isFound is true
//           and the associated Item object (text and meaning) has been 
//           removed from the Dictionary object 
//       else isFound is false or isEmpty is true depending
// usage: myDictionary.deleteEntry(myText, isEmpty, isFound);
void Dictionary::deleteEntry(const Key& targetText, bool& isEmpty, bool& isFound)
{
	int address;
	int indexStop;
	Item topItem;
	
	address = hashFunction(targetText);
	indexStop =  modTABLESIZE(address - 1);
	dictionaryPtr -> hashTablePtr[address].getTop(topItem);
	isFound = topItem == targetText;
	isEmpty = (dictionaryPtr -> numberOfItems == 0);
	
	if(isFound)
	{
		dictionaryPtr -> hashTablePtr[address].pop();
	}
	
	while (!isFound && (address != indexStop))
	{
		deleteFromStack(dictionaryPtr -> hashTablePtr[address], targetText, isFound);
		address = modTABLESIZE(address + 1);
	}	
}
