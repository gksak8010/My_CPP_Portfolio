#include <iostream>
#include "BookContainer.h"

using std::cout;
using std::endl;
using std::cin;


void insertBook(BookContainer& other)
{
	char title[80];
	char author[80];
	int price;

	cout << "도서명 입력: ";
	cin.getline(title, 80);

	cout << "작가 입력: ";
	cin.getline(author, 80);

	cout << "가격 입력: ";
	cin >> price;
	cin.ignore(100, '\n');

	other.addBook(title, author, price);
}

int main()
{
	BookContainer bc; //인스턴스 생성
	while (true)
	{
		cout << "\n\n\t\t* 도서관 프로그램 *\n";
		cout << "\t\t1. 도서 등록\n";
		cout << "\t\t2. 도서 정보 리스트 출력\n";
		cout << "\t\t3. 기준가 이상 도서 리스트 출력\n";
		cout << "\t\t4. 반납 예정 도서 리스트 출력\n";
		cout << "\t\t5. 대여 가능 도서 리스트 출력\n";
		cout << "\t\t6. 도서 대여\n";
		cout << "\t\t0. 프로그램 종료\n";

		cout << "\t\t 메뉴 선택 : ";
		int choice;
		cin >> choice;
		cin.ignore(100, '\n');

		switch (choice)
		{
		case 1:
			insertBook(bc);
			break;
		case 2:
			std::system("cls"); //화면지우기
			cout << "* 도서정보 리스트 출력 *\n";
			bc.displayAllBookInfo();
			break;
		case 3:
			cout << "\t\t검색할 기준 값 입력: ";
			int n;
			cin >> n;
			bc.displayExpensiveBook(n);
			break;
		case 4:
			std::system("cls");
			bc.displayRentalBooks();
			break;
		case 5:
			std::system("cls");
			bc.displayAvailableBooks();
			break;
		case 6:
			cout << "\n\n\t\t대여할 도서명을 입력 하세요: ";
			char title[80];
			cin.ignore();
			cin.getline(title, 80);

			if (bc.borrowBookCon(title))
				cout << "\n\n\t\t도서 대여 성공!\n";
			else
				cout << "\n\n\t\t도서 대여 실패!\n";
			break;
		case 0:
			return 0;
		}
		cout << "\n\n\t\t";
		std::system("pause");	//일시정지
		std::system("cls");		//화면지우기
	}

	return 0;
}