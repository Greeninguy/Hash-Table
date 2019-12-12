// Project4.cpp : Defines the entry point for the console application.
// Main file of Project 4 - Author Jimmie Phelps
//A Student database is created and is linked a hash table.
//User is able to Insert, Delete, and Search for Students in the database.

#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>

#include "Students.h"
#include "HashTable.h"
#include "HashTable.cpp"
#include "Slot.h"

using namespace std;

bool insert(Students &list, HashTable<Students::StudentNode*> &table);
int checkInt(string input);
bool remove(Students &list, HashTable<Students::StudentNode*> &table);
bool searchDisplay(Students &list, HashTable<Students::StudentNode*> &table);
bool printStudent(Students::StudentNode);

void memoryLeakTester();

int main()
{
	//memoryLeakTester();

	Students studentList;
	HashTable<Students::StudentNode*> hashTable;
	string question = "Would you like to (I)nsert, (D)delete a record, (S)earch for a record, or (Q)uit?\nEnter action:  ";
	string input;
	cout << question;
	cin >> input;
	while (input != "Q" && input != "q") {
		if (input == "I" || input == "i") {
			bool inputWorked = insert(studentList, hashTable);
			cout << endl;
			cout << question;
			cin >> input;
		}
		else if (input == "D" || input == "d") {
			bool deleteWorked = remove(studentList, hashTable);
			cout << endl;
			cout << question;
			cin >> input;
		}
		else if (input == "S" || input == "s") {
			bool searchWorked = searchDisplay(studentList, hashTable);
			cout << endl;
			cout << question;
			cin >> input;
		}
		else if (input == "Q" || input == "q") {}
		else {
			cout << "Error:  Enter a correct input (I)sert, (D)elete, (S)earch, or (Q)uit" << endl;
			cout << endl;
			cout << question;
			cin >> input;
		}	
	}
	cout << "Exiting." << endl;

	system("PAUSE");
	return 0;
}

/*
Insert function prompts user to input the information for a new student.  
An Insertion is done to the Students database and a spot on the hash table
	is assigned a pointer to that student.
If the Student ID is not found in the Hash Table, then it will not insert
	and return false.
*/
bool insert(Students &list, HashTable<Students::StudentNode*> &table)
{
	string input, first, last, year;
	int ID;
	Students::StudentNode* k;
	cout << "Inserting a new record." << endl;
	cout << "Last name:  ";
	cin >> last;
	cout << "First name:  ";
	cin >> first;
	cout << "UID:  ";
	cin >> input;
	ID = checkInt(input);
	cout << "Year:  ";
	cin >> year;
	bool alreadyThere = table.find(ID, k);
	if (alreadyThere) {
		cout << "Error:  Record of Student UID " << ID << " already exists." << endl;
		return false;
	}
	list.insert(ID, last, first, year);
	int collisions = 0;
	bool insertWorked = table.insert(ID, list.lastStudent(), collisions);
	cout << "Record inserted." << endl;
	return true;
}

/*
Removes a student from the Students database.  The slot in the hash table becomes a tombstone.
If the student ID is not found in the Hash Table, then it will return false.
*/
bool remove(Students &list, HashTable<Students::StudentNode*> &table)
{
	string input;
	cout << "Enter UID to delete:  ";
	cin >> input;
	int ID = checkInt(input);
	Students::StudentNode *p;
	bool foundIt = table.find(ID, p);
	if (!foundIt) {
		cout << "Did not find record of Student UID " << ID << "." << endl;
		return false;
	}
	bool removeWorked1 = table.remove(ID);
	list.remove(ID);
	cout << "Delete completed." << endl;
	return true;
}

/*
Searches the Hash Table for the input Student ID.  If found it will display the
	student information.
Will return false if the Student ID is not found in the Hash Table.
*/
bool searchDisplay(Students &list, HashTable<Students::StudentNode*> &table)
{
	string input;
	cout << "Enter Student UID to search for:  ";
	cin >> input;
	int ID = checkInt(input);
	cout << "Searching... ";
	Students::StudentNode *p;
	bool foundIt = table.find(ID, p);
	if (foundIt) {
		cout << "record found" << endl;
		cout << "----------------------------" << endl;
		cout << "Last name:  " << p->getLast() << endl;
		cout << "First name:  " << p->getFirst() << endl;
		cout << "UID:  " << p->getId() << endl;
		cout << "Year:  " << p->getYear() << endl;
		cout << "----------------------------" << endl;
		return true;
	}
	cout << "record not found" << endl;
	return false;
}

/*
Memory leak test to ensure dynamically allocated space
	is freed when program ends.
*/
void memoryLeakTester()
{
	string first, last, year = "doople";
	int stu;
	Students list1;
	for (int i = 0; i < 30000; i++) {
		list1.insert(i, first, last, year);
	}
	Students list2;
	for (int i = 0; i < 30000; i++) {
		list2.insert(i, first, last, year);
	}
	Students list3;
	for (int i = 0; i < 30000; i++) {
		list3.insert(i, first, last, year);
	}
}

/*
Helper function which checks for corrent integer input from the user.
If not an intger the program will ask for the correct input.
*/
int checkInt(string input)
{
	int ID;
	bool pass = false;
	while (!pass) {
		bool num = true;
		for (char c : input) {
			if (num == true)
				num = isdigit(c);
		}
		if (num)
			pass = true;
		else {
			cout << "Error: Enter an interger Student UID:  ";
			cin >> input;
		}
	}
	stringstream convert(input);
	convert >> ID;
	return ID;
}