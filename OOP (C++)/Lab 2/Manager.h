/*!
* file: Manager.h
* written: 13/05/2016
* autor: L.Komaryanskiy
* description: this class is realizing new employee type -
* manager, who has unlike common employee own 
* subordinates.
*/
#pragma once

#include "Employee.h"

#include <list>

using namespace std;

class Manager : public Employee
{
public:
	Manager() {};
	Manager(string f_name, string l_name, int age, int id) :
		Employee(f_name, l_name, age, id) {};
	Manager(const Manager& manager);
	Manager& operator=(const Manager& manager);

	virtual void Display(bool show_with_subordinates_list);
	virtual string GetCSV();
	Person* AddSubordinate(Person* person);
	void FireSubordinate(Person* person);
	void FireAllSubordinates();
	void DisplaySubordinates();

private:
	void CopyManager(const Manager& manager);
	//Using this method in copy constructor and assignment operator
	list<Person*> _subordinates;
};