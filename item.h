//username: ltan
//authors: Adam Pesch and Esther Tan
//file name: item.h
// Specification of ADT Item 
//     an Item is-a Key  (technical computer science)
//     class Item is a derived or child class of class Key

//     data object: a meaning of a texting abbreviation
//     operations: create, destroy, copy create, copy
//                 input, output

#ifndef ITEM_H
#define ITEM_H

#include "key.h" 
using namespace std;

class Item: public Key
{
 
//allows for input of an item from either the standard input device or a file
//pre input has been opened and readied for the input of
//    a texting abbreviation followed by newline and associated meaning with
//    spaces between words ending with a newline. For example:
//    lol
//    laugh out loud
//
//post rightHandSideItem has been filled with a texting abbreviation and its
//     associated meaning
//usage cin >> myItem;
friend istream& operator>> (istream& input, Item& rightHandSideItem);
 
//allows for the output of an item to the standard output device or a file
//pre rightHandSideItem has been filled with a texting abbreviation and
//    its associated meaning 
//    output has been opened
//post rightHandSideItem has been written to the output device
//     lol:  laugh out loud
// 
//usage  outfile << myItem;
friend ostream& operator<< (ostream& output, const Item& rightHandSideItem);

public:

//creates an empty item (texting abbreviation and its associated meaning)
//post 
//usage Item aitem;
Item();

//releases memory for a texting abbreviation and its associated meaning
//pre Item object exists
//post Item object no longer exists, memory has been freed
//usage automatically done at the end of scope
~Item();

//creates a new item and copies the right hand side item into item
//pre
//post
//usage  Item myItem(yourItem);
Item(const Item& rightHandSideItem);

//
//pre
//post
//usage
Item& operator=(const Item& rightHandSideItem);

//returns bool value for if an Item is Empty or not
//
//pre 		an Item object exists in memory
//post 		returns true if item is empty, false if not (else)
bool isEmpty();

//marks an Item as deleted
//
//pre 	an Item object is full
//post 	Item object marked with "marked"
//usage	item.markIt();
void markIt();

//returns if an item has been marked or not
//
//pre	an Item object exists in memory
//post	returns true if object has been marked, false if not
//usage	if(anItem.hasBeenMarked())
bool hasBeenMarked();

private:
   string textingMeaning;
};
#endif         