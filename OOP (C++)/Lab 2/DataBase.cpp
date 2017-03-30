#include "DataBase.h"


bool DataBase::SetFileName(const string & file_name)
{
	fstream fs(file_name);
	if (fs.is_open())
	{
		return true;
	}
	return false;
};

bool DataBase::LoadFromFile(const string& file_name)
{
	_file_name = file_name;
	Person* tmp_ptr_person;
	ifstream i_stream(file_name);
	string csv_string;
	if (!i_stream.is_open())
	{
		return false;
	}
	while (!i_stream.eof())
	{
		csv_string = "";
		i_stream >> csv_string;
		tmp_ptr_person = CsvToPerson(csv_string);
		if (tmp_ptr_person != nullptr)
		{
			_employees.push_back(tmp_ptr_person);
			if (typeid(Manager) == typeid(*tmp_ptr_person))
			{
				_managers.push_back(tmp_ptr_person);
			}
		}
	}
	i_stream.close();
};

bool DataBase::SaveFile()
{
	fstream fs(_file_name);
	if (!fs.is_open())
	{
		return false;
	}
	fs.clear();
	for (vector<Person*>::iterator it = _employees.begin(); it != _employees.end(); it++)
	{
		if (typeid(Employee**) == typeid(it))
		{
			fs << dynamic_cast<Employee*>(*it)->GetCSV();
		}
		else
		{
			fs << dynamic_cast<Manager*>(*it)->GetCSV();
		}
		fs << endl;
	}
	return true;
};

bool DataBase::SaveFileAndDelete()
{
	if (SaveFile())
	{
		DeleteWithoutSaving();
		return true;
	}
	return false;
};

void DataBase::DeleteWithoutSaving()
{
	for (vector<Person*>::iterator it = _employees.begin(); it != _employees.end(); it++)
	{
		delete (*it);
	}
};

void DataBase::ArrangeSubordinates()
{
	for (vector<Person*>::iterator it = _managers.begin(); it != _managers.end(); it++)
	{
		dynamic_cast<Manager*>(*it)->FireAllSubordinates();
		for (vector<Person*>::iterator it_sub = _employees.begin(); it_sub != _employees.end(); it_sub++)
		{
			if (typeid(**it_sub) == typeid(Employee))
			{
				if (dynamic_cast<Manager*>(*it)->GetDepartment() == dynamic_cast<Employee*>(*it_sub)->GetDepartment())
				{
					dynamic_cast<Manager*>(*it)->AddSubordinate(*it_sub);
				}
			}
		}
	}
};

Person * DataBase::HireEmlployee(Person * person)
{
	if (person != nullptr)
	{
		_employees.push_back(person);
		if (typeid(Manager*) == typeid(person))
		{
			_managers.push_back(person);
		}
	}
	return person;
};

void DataBase::DisplayDepartmentEmployee(string department)
{
	cout << "In " << department << " work this employees:" << endl;
	for (vector<Person*>::iterator it = _employees.begin(); it != _employees.end(); it++)
	{
		if (typeid(**it) == typeid(Manager))
		{
			if (dynamic_cast<Manager*>(*it)->GetDepartment() == department)
			{
				dynamic_cast<Manager*>(*it)->Display(true);
			}
		}
		else
		{
			if (dynamic_cast<Employee*>(*it)->GetDepartment() == department)
			{
				dynamic_cast<Employee*>(*it)->Display();
			}
		}
	}
};

bool DataBase::FireEmloyee(int id)
{
	Person* ptr_for_deleting;
	for (vector<Person*>::iterator it = _employees.begin(); it != _employees.end(); it++)
	{
		if (typeid(**it) == typeid(Employee))
		{
			//Employee
			if (dynamic_cast<Employee*>(*it)->GetId() == id)
			{
				for (vector<Person*>::iterator it_manager = _managers.begin(); it_manager != _managers.end(); it_manager++)
				{
					if (dynamic_cast<Manager*>(*it_manager)->GetDepartment() == dynamic_cast<Employee*>(*it)->GetDepartment())
					{
						dynamic_cast<Manager*>(*it_manager)->FireSubordinate(*it);
					}
				}
				ptr_for_deleting = *it;
				_employees.erase(it);
				delete ptr_for_deleting;
				return true;
			}
		}
		else if (typeid(**it) == typeid(Manager))
		{
			//Manager
			if (dynamic_cast<Manager*>(*it)->GetId() == id)
			{
				//vector<Person*>::iterator it_manager = _managers.begin();
				//while (it_ma)
				ptr_for_deleting = *it;
				_employees.erase(it);
				_managers.erase(it);
				delete ptr_for_deleting;
				return true;
			}
		}
	}
	return false;
};

void DataBase::DisplayAll()
{
	for (vector<Person*>::iterator it = _employees.begin(); it != _employees.end(); it++)
	{
		if (typeid(**it) == typeid(Employee))
		{
			dynamic_cast<Employee*>(*it)->Display();
		}
		else 
		{
			dynamic_cast<Manager*>(*it)->Display(true);
		}
	}
};

Person * DataBase::CsvToPerson(const string& csv)
{
	Person* ret_value;
	int field_id = 0;
	string tmp_string;

	//data for creation person by constructor
	int tmp_type = 0;
	int tmp_id = 0;
	string tmp_f_name;
	string tmp_l_name;
	int tmp_age = 0;
	string tmp_department;
	int tmp_salary = 0;

	for (int i = 0; i < csv.size(); i++, field_id++)
	{
		tmp_string = "";
		while (i < csv.size() && csv[i] != ';')
		{
			tmp_string += csv[i];
			i++;
		}
		switch (field_id)
		{
		case 0:
		{
			tmp_type = stoi(tmp_string);
			break;
		}
		case 1:
		{
			tmp_id = stoi(tmp_string);
			break;
		}
		case 2:
		{
			tmp_f_name = tmp_string;
			break;
		}
		case 3:
		{
			tmp_l_name = tmp_string;
			break;
		}
		case 4:
		{
			tmp_age = stoi(tmp_string);
			break;
		}
		case 5:
		{
			tmp_department = tmp_string;
			break;
		}
		case 6:
		{
			tmp_salary = stoi(tmp_string);
			break;
		}
		default:
			return nullptr; //error invalid csv
		}
	}
	if (tmp_type == 0)
	{
		//create employee
		ret_value = new Employee(tmp_f_name, tmp_l_name, tmp_age, tmp_id);
		dynamic_cast<Employee*>(ret_value)->SetDepartment(tmp_department);
		dynamic_cast<Employee*>(ret_value)->SetSalary(tmp_salary);
		return ret_value;
	}
	else if (tmp_type == 1)
	{
		//create manager
		ret_value = new Manager(tmp_f_name, tmp_l_name, tmp_age, tmp_id);
		dynamic_cast<Manager*>(ret_value)->SetDepartment(tmp_department);
		dynamic_cast<Manager*>(ret_value)->SetSalary(tmp_salary);
		return ret_value;
	}
	return nullptr;//error, undefined person type
};

DataBase::~DataBase()
{
	DeleteWithoutSaving();
};