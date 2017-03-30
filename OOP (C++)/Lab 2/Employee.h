/*!
* file: Employee.h
* written: 13/05/2016
* autor: L.Komaryanskiy
* description: class description common 
* employee that inherit abstract class Person.
*/
#pragma once

#include "Person.h"

using namespace std;

class Employee : public Person
{
public:
	//constructors
	Employee() {};
	Employee(string f_name, string l_name, int age, int id) :
		Person(f_name, l_name, age), _id(id) {};
	Employee(const Employee& employee);
	Employee& operator=(const Employee& employee);

	//public methods
	void SetSalary(int new_salary);
	void SetDepartment(const string& new_department);
	void SetId(int id);
	int GetId();
	string GetDepartment();
	virtual void Display();
	virtual string GetCSV();

protected:
	string _department;
	int _salary;
	int _id;

private:
	//Using this method in copy constructor and assignment operator
	void CopyEmployee(const Employee& employee);
};
