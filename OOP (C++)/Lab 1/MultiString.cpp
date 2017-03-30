#include "MultiString.h"


MultiString::MultiString()
{
	_str_nmb = 0;
	_data = new char*;
	_data[0] = new char();
	_data[0][0] = '\0';
};

MultiString::MultiString(int size)
{
	_str_nmb = size;
	_data = new char*[_str_nmb];
	for (int i = 0; i < _str_nmb; i++) 
	{
		_data[i] = new char;
		_data[i][0] = '\0';
	}
};

MultiString::~MultiString()
{
	for (int i = 0; i < _str_nmb; i++) 
	{
		delete[] _data[i];
	}
	delete[]_data;
};

MultiString &MultiString::operator=(const MultiString & ms)
{
	for (int i = 0; i < _str_nmb; i++)
	{
		delete[] _data[i];
	}
	delete[] _data;
	_data = new char*[ms._str_nmb + 1];
	for (int i = 0; i < ms._str_nmb; i++)
	{
		strcpy(_data[i], ms._data[i]);
	}
	return *this;
};

char *MultiString::operator[](int nIndex) const
{
	char *ret_value = new char[strlen(_data[nIndex]) + 1];
	strcpy(ret_value, _data[nIndex]);
	return ret_value;
};

MultiString &MultiString::operator+=(const MultiString &concat_multiString)
{
	//test for exception assignement the same object
	if (this == &concat_multiString)
	{
		return *this;
	}
	char **buf = new char*[_str_nmb + concat_multiString._str_nmb];
	//copy source data to buffer
	for (int i = 0; i < _str_nmb; i++)
	{
		buf[i] = new char[strlen(_data[i]) + 1];
		strcpy(buf[i], _data[i]);
	}
	for (int i = 0; i < _str_nmb; i++)
	{
		delete[] _data[i];
	}
	delete[] _data;
	//copy multistring
	for (int i = 0; i < concat_multiString._str_nmb; i++)
	{
		buf[i + _str_nmb] = new char[strlen(concat_multiString._data[i]) + 1];
		strcpy(buf[i + _str_nmb], concat_multiString._data[i]);
	}
	_str_nmb += concat_multiString._str_nmb;
	_data = buf;
	return *this;
};

void MultiString::MergeMultiStringExclusive(const MultiString &concat_multiString)
{
	//count how much increase source vector
	int diff_strings = 0;
	for (int i = 0; i < concat_multiString._str_nmb; i++) 
	{
		if (Find(concat_multiString._data[i]) < 0)
		{
			diff_strings++;
		}
	}
	if (diff_strings != 0)
	{
		char **buf = new char*[_str_nmb + diff_strings];//use buf
		//copy source data to buffer
		for (int i = 0; i < _str_nmb; i++)
		{
			buf[i] = new char[strlen(_data[i]) + 1];
			strcpy(buf[i], _data[i]);
		}
		//add different strings to buf multistring
		for (int i = 0; i < concat_multiString._str_nmb; i++)
		{
			if (Find(concat_multiString._data[i]) < 0)
			{
				buf[i + _str_nmb - 1] = new char[strlen(concat_multiString._data[i]) + 1];
				strcpy(buf[i + _str_nmb - 1], concat_multiString._data[i]);
			}
		}
		//clear source multistring
		for (int i = 0; i < _str_nmb; i++)
		{
			delete[] _data[i];
		}
		delete[] _data;

		_str_nmb += diff_strings;
		_data = buf;
	}
};

int MultiString::Find(const char * pszSub) const
{
	for (int i = 0; i < _str_nmb; i++) 
	{
		if (strcmp(_data[i], pszSub) == 0)
		{
			//string found
			return i;
		}
	}
	//if reached for this place then string not found
	return -1;
};

void MultiString::Empty()
{
	for (int i = 0; i < _str_nmb; i++) 
	{
		delete[] _data[i];
	}
	delete[] _data;
	_data = new char*;
	*_data = new char;
	**_data = '\0';
	_str_nmb = 0;
};

void MultiString::SetAt(int nIndex, const char *str)
{
	delete[] _data[nIndex];
	_data[nIndex] = new char[strlen(str) + 1];
	strcpy(_data[nIndex], str);
};

void MultiString::PrintStr(int nIndex) const
{
	printf("%s\n",_data[nIndex]);
};

void MultiString::PrintAllStr() const
{
	for (int i = 0; i < _str_nmb; i++) {
		printf("%s%\n",_data[i]);
	}
};
