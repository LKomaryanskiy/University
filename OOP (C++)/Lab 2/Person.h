/*!
* file: Person.h
* written: 13/05/2016
* autor: L.Komaryanskiy
* description: it's a abstract class that
* has basic members (first and last name person) 
* and virtual method that need to 
* overloading in sub classes.
*/
#pragma once
#include <string>
#include <iostream>

using namespace std;

class Person
{
public:
	Person() {};
	Person(string f_name, string l_name, int age) : 
		_first_name(f_name), _last_name(l_name), _age(age) {};
	virtual void Display() = 0;

protected:
	string _first_name;
	string _last_name;
	int _age;
};
