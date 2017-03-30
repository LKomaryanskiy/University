/*!
* file: MultiString.h
* MultiString class definition
* written: 01/05/2016
* autor: L.Komaryanskiy
*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>

class MultiString {
public:
	/*constructors && destructor*/
	MultiString();
	MultiString(int);
	virtual ~MultiString();

	/*methods*/
	MultiString & operator=(const MultiString &ms);
	char * operator[] (int nIndex) const;
	MultiString & operator+=(const MultiString &);
	void MergeMultiStringExclusive(const MultiString &);
	/*return negative number, if string is not found*/
	int Find(const char *pszSub) const;
	inline int GetLength() const { return _str_nmb; };
	inline bool IsEmpty() const { return _str_nmb == 0; };
	void Empty();
	void SetAt(int nIndex, const char* str);
	void PrintStr(int nIndex) const;
	void PrintAllStr() const;
private:
	/*forbidden copy constructor*/
	MultiString(const MultiString & ms) {};

	/*members*/
	char **_data;//pointer to vector
	int _str_nmb;//strings number
};

