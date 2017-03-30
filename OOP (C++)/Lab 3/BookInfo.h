/*!
* file: BookInfo.h
* written: 1/06/2016
* autor: L.Komaryanskiy
* description: class with basic
* information about books. Created for
* testing template class binary search tree.
*/
#pragma once
#include <string>

using namespace std;

class BookInfo
{
public:
	BookInfo() :
		_book_id(0), _author("Unknown"), _title("Unknown"), _year(1812), _quantity(1) {};
	BookInfo(int book_id, string author = "Unknown", string title = "Unknown", int year = 1812, int quantity = 1) :
		_book_id(book_id), _author(author), _title(title), _year(year), _quantity(quantity) {};
	BookInfo(const BookInfo& book_info);
	~BookInfo() {};

	void SetId(int new_id);
	void SetAuthor(const string& new_author);
	void SetTitle(const string& new_title);
	void SetYear(int new_year);
	void SetQuantity(int new_quantity);

	int GetBookId();
	string GetAuthor();
	string GetTitle();
	int GetYear();
	int GerQuantity();

	friend ostream& operator<<(ostream& os, const BookInfo& book_info);
	BookInfo& operator=(const BookInfo& book_info);
	friend bool operator==(const BookInfo& left_book, const BookInfo& right_book);
	friend bool operator<(const BookInfo& left_book, const BookInfo& right_book);
	friend bool operator>(const BookInfo& left_book, const BookInfo& right_book);
	
protected:
	int _book_id;
	string _author;
	string _title;
	int _year;
	int _quantity;

private:
	void CopyBook(const BookInfo& book_info);
};
