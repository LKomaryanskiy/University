#include "BookInfo.h"

BookInfo::BookInfo(const BookInfo & book_info)
{
	CopyBook(book_info);
};

void BookInfo::SetId(int new_id)
{
	_book_id = new_id;
};

void BookInfo::SetAuthor(const string& new_author)
{
	_author = new_author;
};

void BookInfo::SetTitle(const string& new_title)
{
	_title = new_title;
};

void BookInfo::SetYear(int new_year)
{
	_year = new_year;
};

void BookInfo::SetQuantity(int new_quantity)
{
	_quantity = new_quantity;
};

int BookInfo::GetBookId()
{
	return _book_id;
};

string BookInfo::GetAuthor()
{
	return _author;
};

string BookInfo::GetTitle()
{
	return _title;
};

int BookInfo::GetYear()
{
	return _year;
};

int BookInfo::GerQuantity()
{
	return _quantity;
};

BookInfo & BookInfo::operator=(const BookInfo & book_info)
{
	CopyBook(book_info);
	return *this;
};

bool operator==(const BookInfo& left_book, const BookInfo& right_book)
{
	if (left_book._book_id == right_book._book_id)
	{
		return true;
	}
	return false;
};

bool operator<(const BookInfo& left_book, const BookInfo& right_book)
{
	if (left_book._book_id < right_book._book_id)
	{
		return true;
	}
	return false;
};

bool operator>(const BookInfo& left_book, const BookInfo& right_book)
{
	if ((left_book < right_book)
		|| (left_book == right_book))
	{
		return false;
	}
	return true;
};

void BookInfo::CopyBook(const BookInfo & book_info)
{
	if (this != &book_info)
	{
		this->_author = book_info._author;
		this->_book_id = book_info._book_id;
		this->_quantity = book_info._quantity;
		this->_title = book_info._title;
		this->_year = book_info._year;
	}
};

ostream & operator<<(ostream & os, const BookInfo & book_info)
{
	os << "Title: " << book_info._title << " Author: " << book_info._author << endl;
	os << "Book ID: " << book_info._book_id << " Year: " << book_info._year << " Quantity: " << book_info._quantity;
	return os;
}
