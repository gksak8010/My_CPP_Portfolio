#include "BookContainer.h"
#include <iostream>

void BookContainer::addBook(const char* title, const char* author, int price)
{
	if (index < BOOK_SIZE)
		p[index] = new Book(title, author, price); //Book 인스턴스 생성
}

void BookContainer::displayAllBookInfo() const
{
	for (int i = 0; i < index; i++)
		p[i]->displayBookInfo();
}

void BookContainer::displayExpensiveBook(int minPrice)
{
	std::cout << "* " << minPrice << "원 이상 도서 리스트 출력 *\n";
	for (int i = 0; i < index; i++)
	{
		if (p[i]->getPrice() >= minPrice)
			p[i]->displayBookInfo();
	}
}

bool BookContainer::borrowBookCon(const char* target)
{
	for (int i = 0; i < index; i++)
	{
		if (std::strcmp(target, p[i]->getTitle()) == 0) //검색한 도서가 존재한다면?
		{
			return p[i]->Rental();
		}
	}
	return false;
}

BookContainer::~BookContainer()
{
	for (int i = 0; i < index; i++)
		delete p[i]; //동적으로 생성된 인스턴스 제거
}
