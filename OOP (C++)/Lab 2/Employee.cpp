#include "Employee.h"

void Employee::CopyEmployee(const Employee & employee)
{
	//Checking for assignment the same object
	if (this != &employee)
	{
		this->_first_name = employee._first_name;
		this->_last_name = employee._last_name;
		this->_age = employee._age;
		this->_department = employee._department;
		this->_salary = employee._salary;
	}
};

Employee::Employee(const Employee & employee)
{
	CopyEmployee(employee);
};

Employee & Employee::operator=(const Employee & employee)
{
	CopyEmployee(employee);
	return *this;
};

void Employee::SetSalary(int new_salary)
{
	_salary = new_salary;
};

void Employee::SetDepartment(const string& new_department)
{
	_department = new_department;
};

void Employee::SetId(int id)
{
	_id = id;
};

int Employee::GetId()
{
	return _id;
};

string Employee::GetDepartment()
{
	return _department;
};

void Employee::Display()
{
	cout << "Employment type: employee" << endl;
	cout << "ID:" << _id << endl;
	cout << _first_name << " " << _last_name << " age: " << _age << " salary: " << _salary << endl;
	cout << "department: " << _department << endl << endl;
};

string Employee::GetCSV()
{
	string ret_value;
	ret_value = "0;" + to_string(_id) + ';' + _first_name + ';' + _last_name + ';' + to_string(_age) + ';' + _department + ';' + to_string(_salary);
	return ret_value;
};
