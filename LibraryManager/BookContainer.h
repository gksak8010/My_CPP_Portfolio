#pragma once

#include "Book.h"

class BookContainer
{
public:
	void addBook(const char* title, const char* author, int price);
	void displayAllBookInfo() const;
	void displayExpensiveBook(int minPrice);
	bool borrowBookCon(const char* target);

public:
	~BookContainer();
private:
	static const int BOOK_SIZE = 100;
	Book* p[BOOK_SIZE] = {nullptr}; //포인터 변수 100개 선언
	int index;
};