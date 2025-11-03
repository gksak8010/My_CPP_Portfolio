#pragma once

class Book
{
public:
	//대여중이야? 대여체크함수 : 대여중이면 true, 아니라면 false
	bool isRentalCheck() const { return isBorrowed; }
	//대여 함수: 아직 대여되지 않았다면? 대여(true)
	bool Rental();
	//반납 함수: 아직 대여중이라면? 반납(false)
	bool RentalReturn();
	void displayBookInfo();
public:
	Book();
	Book(const char* title, const char* author, int price);
	//복사생성자
	Book(const Book& other);
	//소멸자
	~Book();

	//get
	inline const char* getTitle() const { return title; }
	inline const char* getAuthor() const { return author; }
	inline int getPrice() const { return price; }
	//set
	void setTitle(const char* title);
	void setAuthor(const char* author);
	inline void setPrice(int price) { this->price = price; }

private:
	char* title = nullptr;
	char* author = nullptr;
	int price = 0;
	bool isBorrowed = false; //대여상태
};