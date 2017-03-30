#include "Manager.h"

Manager::Manager(const Manager & manager)
{
	CopyManager(manager);
};

Manager & Manager::operator=(const Manager & manager)
{
	CopyManager(manager);
	return *this;
};

void Manager::Display(bool show_with_subordinates_list)
{
	cout << "Employment type: manager" << endl;
	cout << "ID:" << _id << endl;
	cout << _first_name << " " << _last_name << " age: " << _age << " salary: " << _salary << endl;
	cout << "department: " << _department << endl;
	if (show_with_subordinates_list)
	{
		DisplaySubordinates();
	}
};

string Manager::GetCSV()
{
	string ret_value;
	ret_value = "1;" + to_string(_id) + ';' + _first_name + ';' + _last_name + ';' + to_string(_age) + ';' + _department + ';' + to_string(_salary);
	return ret_value;
};

Person * Manager::AddSubordinate(Person * person)
{
	if (person != nullptr)
	{
		_subordinates.push_back(person);
		return person;
	}
	return nullptr;
};

void Manager::FireSubordinate(Person * person)
{
	for (list<Person*>::iterator it = _subordinates.begin(); it != _subordinates.end(); it++)
	{
		if ((*it) == person)
		{
			_subordinates.erase(it);
			return;
		}
	}
};

void Manager::FireAllSubordinates()
{
	_subordinates.clear();
};

void Manager::DisplaySubordinates()
{
	cout << '\t' << "Subordinates:" << endl;
	for (list<Person*>::iterator it = _subordinates.begin(); it != _subordinates.end(); it++)
	{
		(*it)->Display();
	}
	cout << '\t' << "--------------------" << endl;
	cout << endl;
};

void Manager::CopyManager(const Manager& manager)
{
	//Checking for assignment the same object
	if (this != &manager)
	{
		this->_first_name = manager._first_name;
		this->_last_name = manager._last_name;
		this->_age = manager._age;
		this->_salary = manager._salary;
		this->_id = manager._id;
		this->_subordinates = manager._subordinates;
	}
};
