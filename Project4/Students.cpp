#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "Students.h"

using namespace std;


/*
Insert member function enters creates a StudentNode Object and inserts it into the linked list of Students.
*/
void Students::insert(int id, string last, string first, string year)
{
	if (!root) {
		root = new StudentNode(id, last, first, year);
	}
	STUDENTPTR p = root;
	while (p->after) {
		p = p->after;
	}
	p->after = new StudentNode(id, last, first, year);
	p->after->before = p;
}

/*
Removes and deletes a student from the Students linked list.
Repairs the linked list to bridge any holes made from the removal.
If the Student ID is not found in the list, then returns false.
*/
bool Students::remove(int id)
{
	STUDENTPTR p = root;
	if (p->getId() == id) {
		if (p->after)
			root = p->after;
		else 
			root = NULL;
		delete p;
		return true;
	}
	while (p->after) {
		p = p->after;
		if (p->getId() == id) {
			if (p->after) {
				p->before->after = p->after;
				p->after->before = p->before;
				delete p;
			}
			else {
				p->before = NULL;
				delete p;
			}
			return true;
		}
	}
	return false;
}

/*
Helper function used by Main's insert member function.  
Traverses to the end of the linked list and returns the last student.
*/
Students::STUDENTPTR Students::lastStudent()
{
	STUDENTPTR p = root;
	while (p->after) {
		p = p->after;
	}
	return p;

}

Students::Students()
{
	root = NULL;
}


Students::~Students()
{
	if (root) {
		STUDENTPTR p = root;
		STUDENTPTR next = root;
		while (p->after) {
			next = next->after;
			delete p;
			p = next;
		}
		delete p;
	}
}

Students::StudentNode::StudentNode(int id, string last, string first, string year)
{
	studentID = id;
	lastName = last;
	firstName = first;
	studentYear = year;
	before = NULL;
	after = NULL;
}

int Students::StudentNode::getId()
{
	return studentID;
}

string Students::StudentNode::getLast()
{
	return lastName;
}

string Students::StudentNode::getFirst()
{
	return firstName;
}

string Students::StudentNode::getYear()
{
	return studentYear;
}

