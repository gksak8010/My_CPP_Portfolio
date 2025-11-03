#include "Book.h"
#include <cstring>
#include <iostream>

#pragma warning (disable:4996)

bool Book::Rental()
{
	if (!isBorrowed)
	{
		isBorrowed = true;
		return true;
	}
	return false;
}
//반납 함수: 아직 대여중이라면? 반납(false)
bool Book::RentalReturn()
{
	if (isBorrowed)
	{
		isBorrowed = false;
		return true;
	}
	return false;
}

void Book::displayBookInfo()
{
	std::cout << "[도서명: " << title << "작가: " << author << "가격: " << price << "대여상태: " << (isBorrowed ? "대여중" : "도서보유중") << "]\n";
}

Book::Book()
{
	//책제목: Unknown, 작가: Unknown, 가격: 0으로 초기화
	title = new char[8];
	strcpy(title, "Unknown");

	author = new char[8];
	std::strcpy(author, "Unknown");

	price = 0;
	isBorrowed = false;
}

Book::Book(const char* title, const char* author, int price)
{
	//메개변수의 값으로 초기화
	this->title = new char[std::strlen(title) + 1];
	std::strcpy(this->title, title);

	this->author = new char[std::strlen(author) + 1];
	std::strcpy(this->author, author);

	this->price = price;
	isBorrowed = false;
}

Book::~Book()
{
}

void Book::setTitle(const char* title)
{
	if (this->title != nullptr)
		delete[] this->title;

	this->title = new char[std::strlen(title) + 1];
	strncpy(this->title, title, strlen(title) + 1);
}

void Book::setAuthor(const char* author)
{
	if (this->author != nullptr)
		delete[] this->author;

	this->author = new char[std::strlen(author) + 1];
	strncpy(this->author, author, strlen(author) + 1);
}

Book::Book(const Book& other) : Book(other.title, other.author, other.price) //생성자 호출
{
}
