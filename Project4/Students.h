#pragma once

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#define STUDENTPTR StudentNode*

/*
Students Object is a linked list of StudentNodes used to store and organize Students.
*/
class Students
{

public:

	/*
	StudentNode Object holds Student information and a few functionalities.
	*/
	class StudentNode {
	public:
		STUDENTPTR before;
		STUDENTPTR after;

		StudentNode(int id, string last, string first, string year);
		int getId();
		string getLast();
		string getFirst();
		string getYear();
		

	private:
		int studentID;
		string lastName;
		string firstName;
		string studentYear;
	};

	void insert(int id, string last, string first, string year);
	bool remove(int id);
	STUDENTPTR lastStudent();
	Students();
	~Students();

private:
	STUDENTPTR root;
};

