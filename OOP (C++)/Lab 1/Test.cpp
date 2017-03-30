#include "MultiString.h"

#include <stdlib.h>


int main() 
{
	/*test default constructor*/
	MultiString *empty_multi_string = new MultiString();
	/*test constructor where indicated size*/
	MultiString *first_test_ms = new MultiString(1);
	MultiString *second_test_ms = new MultiString(2);
	MultiString *third_test_ms = new MultiString(2);
	/*tets SetAt method*/
	first_test_ms->SetAt(0, "C++");
	printf("First multi string:\n");
	first_test_ms->PrintStr(0);
	system("pause");
	system("cls");

	second_test_ms->SetAt(0, "one");
	second_test_ms->SetAt(1, "love");
	printf("Second multi string:\n");
	second_test_ms->PrintAllStr();
	system("pause");
	system("cls");

	third_test_ms->SetAt(0, "C++");
	third_test_ms->SetAt(1, "!");
	printf("Third multi string:\n");
	third_test_ms->PrintAllStr();
	system("pause");
	system("cls");

	/*tets += operator*/
	*first_test_ms += *second_test_ms;
	printf("First multi string after test \"+=\" operator with second multi string:\n");
	first_test_ms->PrintAllStr();
	system("pause");
	system("cls");

	/*test empty method*/
	second_test_ms->Empty();
	printf("Second multi string after test empty method:\n");
	second_test_ms->PrintAllStr();
	system("pause");
	system("cls");

	/*test exclusive merge method*/
	first_test_ms->MergeMultiStringExclusive(*third_test_ms);
	printf("First multi string after test Merge Exclusive with third multi string:\n");
	first_test_ms->PrintAllStr();
	system("pause");
	system("cls");

	/*tets isEmpty and getlength methods*/
	if (!first_test_ms->IsEmpty()) 
	{
		printf("%s%d\n","First multi string is not empty and has length: ", first_test_ms->GetLength());
	}
	system("pause");
	system("cls");

	if (empty_multi_string->IsEmpty())
	{
		printf("Empty multi string is empty (pardon the tautology =) )\n");
	}
	system("pause");
	system("cls");

	/*tets find method*/
	if (first_test_ms->Find("C++") >= 0)
	{
		printf("%s%d%s\n", "\"C++\" is found in first test multi string on ", first_test_ms->Find("C++"), "position");
	}
	system("pause");
	system("cls");

	if (third_test_ms->Find("love") < 0)
	{
		printf("\"love\" is not flound in third multistring");
	}
	system("pause");

	/*free memory*/
	delete empty_multi_string;
	delete first_test_ms;
	delete second_test_ms;
	return 0;
};