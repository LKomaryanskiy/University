#include "DataBase.h"

int main()
{
	DataBase* db = new DataBase;
	db->LoadFromFile("Base.txt");
	db->ArrangeSubordinates();
	db->DisplayAll();
	system("pause");
	system("cls");

	//fire employee
	cout << "Fire employee with ID number 1 (he didn't work hard =( )" << endl;
	db->FireEmloyee(1);
	db->ArrangeSubordinates();
	db->DisplayAll();
	system("pause");
	system("cls");

	//hire new employee
	//create new common employee
	Person* new_employee = new Employee("Howard", "Wolowitz", 25, 7);
	dynamic_cast<Employee*>(new_employee)->SetDepartment("Scientist");
	dynamic_cast<Employee*>(new_employee)->SetSalary(1300);
	db->HireEmlployee(new_employee);
	cout << "Hire new employee" << endl;
	db->ArrangeSubordinates();
	db->DisplayAll();
	system("pause");
	system("cls");

	//display department
	db->DisplayDepartmentEmployee("IT");
	system("pause");
	system("cls");

	delete db;
	cout << "Database was deleted" << endl;
	system("pause");
	return 0;
};
