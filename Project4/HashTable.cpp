#include "stdafx.h"
#include <stdlib.h>    
#include <algorithm>
#include <array>
#include <iostream>
#include <iomanip>

#include "HashTable.h"

using namespace std;

/*
Hash function used to generate random Hash Table spots.
This code was posted by Thomas Mueller on Stackoverflow.com
https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
*/
template<class T>
int HashTable<T>::hashIt(unsigned int key)
{
	int x = key;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	x = x % 999;
	return x;
}

/*
Insert member function inserts a templated value into a hashed spot of
the Hash Table in relation to the key.  
Collisions are tracked to see how extensive probing was required for the insertion.
*/
template<class T>
bool HashTable<T>::insert(int key, T value, int & collisions)
{
	collisions = 0;
	int home = hashIt(key);
	bool normal;
	bool found;
	int slotKey = 0;
	found = this->find(key, value);		//Uses find member function to check if the key has already been used.
	if (found) {
		cout << "Key is already in database." << endl;
		return false;
	}
	normal = table[home].isNormal();		//If home spot on the Hash Table is empty or a tombstone, straightfoward insertion is possible.
	if (!normal) {
		table[home] = Slot<T>(key, value);
		return true;
	}
	else {
		int newHome = 0;				//Psedo-random probing is done in case home spot on the Hash Table is not empty or a tombstone.
		for (int i = 0; i < MAXHASH - 1; i++) {
			newHome = home + probeArray[i];
			newHome = newHome % 999;
			normal = table[newHome].isNormal();
			if (!normal) {
				table[newHome] = Slot<T>(key, value);
				return true;
			}
			collisions++;
		}
	}
	cout << "Could not insert data, table is full." << endl;
	return false;
}

/*
Remove member function locates the corresponding key spot and turns it into a tombstone Slot.
Returns false if the key is not found in the Hash Table.
*/
template<class T>
bool HashTable<T>::remove(int key)
{
	T value;
	int newHome = 0;
	int home = hashIt(key);
	int slotKey = 0;
	bool empty = table[home].isEmpty();
	bool found;
	found = this->find(key, value);
	if (!found)
		return false;
	bool normal = table[home].isNormal();
	if (normal) {
		slotKey = table[home].getKey();
		if (slotKey == key) {
			table[home].kill();
			return true;
		}
	}
	for (int i = 0; i < MAXHASH - 1; i++) {		//Probing done if the home slot is not empty, or the key being searched
		newHome = home + probeArray[i];
		newHome = newHome % 999;
		empty = table[newHome].isEmpty();
		if (empty)
			return false;
		else {
			normal = table[newHome].isNormal();
			if (normal) {
				slotKey = table[newHome].getKey();
				if (slotKey == key) {
					table[newHome].kill();
					return true;
				}
			}
		}
	}
	return false;
}

/*
Find member function searches the Hash Table for a normal Slot with the corresponding key.
Returns if not found in the Hash Table.  If found, the Slot's value can be refferenced by the member function.
*/
template<class T>
bool HashTable<T>::find(int key, T & value)
{
	int homeKey = 0;
	int newHome = 0;
	int home = hashIt(key);
	bool empty = table[home].isEmpty();
	if (empty)
		return false;
	else {
		bool normal = table[home].isNormal();
		if (normal) {
			homeKey = table[home].getKey();
			if (homeKey == key) {
				value = table[home].getValue();
				return true;
			}
		}
		for (int i = 0; i < MAXHASH - 1; i++) {
			newHome = home + probeArray[i];
			newHome = newHome % 999;
			empty = table[newHome].isEmpty();
			if (empty)
				return false;
			else {
				normal = table[newHome].isNormal();
				if (normal) {
					homeKey = table[newHome].getKey();
					if (homeKey == key) {
						value = table[newHome].getValue();
						return true;
					}
				}
			}
		}
		return false;
	}
}

/*
Returns a ratio to Empty Slots to the total.
*/
template<class T>
float HashTable<T>::alpha()
{
	bool empty;
	float den = 0;
	float alpha;
	for (int i = 0; i < MAXHASH; i++) {
		empty = table[i].isEmpty();
		if (!empty) {
			den++;
		}
	}
	alpha = den / MAXHASH;
	return alpha;
}

/*
Constructor creates array used for psudo-random probing.
*/
template<class T>
HashTable<T>::HashTable()
{
	for (int i = 0; i < MAXHASH -1; i++) {
		probeArray[i] = i + 1;
	}
	random_shuffle(begin(probeArray), end(probeArray));
}

template<class T>
HashTable<T>::~HashTable()
{
}

template<class T>
ostream& operator<<(ostream& os, const HashTable<T>& me)
{
	Slot<T> t;
	int j;
	for (int i = 0; i < MAXHASH; i++) {
		j = i;
		t = me.table[i];
		os << "Slot " << j << endl;
		os << t << endl;
	}
	return os;
}
