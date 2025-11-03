#include <iostream>
#include "StudentContainer.h"

using std::cout;
using std::endl;
using std::cin;

void insertStudent(StudentContainer& other)
{
	char Name[80];
	int Grade;
	int Class;
	int kor;
	int mat;
	int eng;

	cout << "학생 이름 입력: ";
	cin.getline(Name, 80);

	cout << "학년 입력: ";
	cin >> Grade;

	cout << "반 입력: ";
	cin >> Class;

	cout << "국어 성적 입력: ";
	cin >> kor;

	cout << "수학 성적 입력: ";
	cin >> mat;

	cout << "영어 성적 입력: ";
	cin >> eng;

	other.addStudent(Name, Grade, Class, kor, mat, eng);
}

int main()
{
	StudentContainer sc;

	while (true)
	{
		cout << "\n\n\t\t* 성적관리 프로그램 *\n";
		cout << "\n\n\t\t1. 학생 등록\n";
		cout << "\n\n\t\t2. 총 학생 리스트 출력\n";
		cout << "\n\n\t\t3. 학생 찾기\n";
		cout << "\n\n\t\t4. 학생 정보 수정\n";
		cout << "\n\n\t\t5. 학생 삭제\n";

		cout << "\t\t 메뉴 선택 : ";
		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
			insertStudent(sc);
			break;
		case 2:
			std::system("cls");
			cout << "* 총 학생정보 리스트 출력 *\n";
			sc.displayAllStudentInfo();
			break;
		case 3:
			char target[80];
			cout << "찾을 학생의 이름을 적으세요 : " << endl;
			cin.getline(target, 80);

			sc.targetStudent(target);
			break;
		case 4:
			char targe[80];
			cout << "수정할 학생의 이름을 적으세요 : " << endl;
			cin.getline(target, 80);

			sc.modifyTarget(target);
			break;
		case 5:
			sc.deleteTarget(target);
			break;
		}
	}

	return 0;
}