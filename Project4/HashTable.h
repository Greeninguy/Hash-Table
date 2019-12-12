#pragma once

#include <iostream>
#include <iomanip>
#include "Slot.h"

#define MAXHASH 1000

using namespace std;

/*
HashTable object has the functionality of a hash table to allow for rapid searching of template T items.
Standard size of the hash table is set at 1000.
*/
template<class T> class HashTable
{

private:

	Slot<T> table[MAXHASH];
	int probeArray[MAXHASH - 1];

public:
	int hashIt(unsigned int key);
	bool insert(int key, T value, int& collisions);
	bool remove(int key);
	bool find(int key, T& value);
	float alpha();
	template <class T>
	friend ostream& operator<<(ostream& os, const HashTable<T>& me);
	HashTable();
	~HashTable();

};
