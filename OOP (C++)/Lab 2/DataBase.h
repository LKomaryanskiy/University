/*!
* file: Person.h
* written: 13/05/2016
* autor: L.Komaryanskiy
* description: data base with two employee
* type - manager and common employee. Data
* base can be loaded from file.
*/
#pragma once

#include "Manager.h"

#include <vector>
#include <fstream>

using namespace std;

class DataBase
{
public:
	DataBase() :
		_file_name("tmp_save.txt"){};
	virtual ~DataBase();

	bool SetFileName(const string& file_name);
	bool LoadFromFile(const string& file_name);
	//return true if changes were saved
	bool SaveFile();
	//doesn't delete if can't save
	bool SaveFileAndDelete();
	void DeleteWithoutSaving();
	/*this method arranging employees by its own departments*/
	void ArrangeSubordinates();
	Person* HireEmlployee(Person* person);
	void DisplayDepartmentEmployee(string department);
	bool FireEmloyee(int id);
	void DisplayAll();

protected:
	vector<Person*> _employees;
	vector<Person*> _managers;
	string _file_name;
private:
	/*Return pointer to person. If csv isn't valid - return nullptr*/
	Person* CsvToPerson(const string& csv);
};
