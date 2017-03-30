#include "BookInfo.h"
#include "BinTree.h"

int main()
{
	BinTree<BookInfo>* tree = new BinTree<BookInfo>();
	BookInfo book1(40350, "Nicholas A. Solter, Scott J. Kleper ", "Professional C++", 2005, 130);
	BookInfo book2(15697, "Bjarne Stroustrup", " The C++ Programming Language (Fourth Edition)", 2013, 45);
	BookInfo book3(30324, "Herbert Schildt", "C++: The Complete Reference", 1991, 32);
	BookInfo book4(60123, "Frank Luna", "Introduction to 3D Game Programming with DirectX 11", 2012, 4);
	BookInfo book5(45703, "George Martin", "A Dance with Dragons", 2011, 1054);
	tree->AddItem(book1);
	tree->AddItem(book2);
	tree->AddItem(book3);
	tree->AddItem(book4);
	tree->AddItem(book5);

	tree->Print();
	system("pause");
	system("cls");

	tree->FindAndDeleteItem(book4);
	tree->Print();
	system("pause");
	system("cls");

	delete tree;
	return 0;
}