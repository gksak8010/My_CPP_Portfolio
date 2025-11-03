#include "StudentContainer.h"
#include <iostream>

void StudentContainer::addStudent(const char* Name, int Grade, int Class, int kor, int mat, int eng)
{
	if (index < STUDENT_SIZE)
		p[index] = new Student(Name, Grade, Class, kor, mat, eng);
}

void StudentContainer::displayAllStudentInfo() const
{
	for (int i = 0; i < index; i++)
		p[i]->displayStudentInfo();
}

void StudentContainer::targetStudent(const char* target)
{
	for (int i = 0; i < index; i++)
	{
		if (std::strcmp(target, p[i]->getName()) == 0) //학생이 존재한다면
		{
			return p[i]->displayStudentInfo();
		}
		else
			std::cout << "학생이 존재하지 않습니다." << std::endl;
	}
}

void StudentContainer::modifyTarget(const char* target)
{
	for (int i = 0; i < index; i++)
	{
		if (std::strcmp(target, p[i]->getName()) == 0) //학생이 존재한다면
		{
			char newName[80];
			std::cout << "새로운 이름을 입력하세요 : ";
			std::cin.getline(newName, 80);
			p[i]->setName(newName);

			int newGrade;
			std::cout << "새로운 학년을 입력하세요 : ";
			std::cin >> newGrade;
			p[i]->setGrade(newGrade);

			int newClass;
			std::cout << "새로운 반을 입력하세요 : ";
			std::cin >> newClass;
			p[i]->setClass(newClass);

			int newKor;
			std::cout << "새로운 국어 성적을 입력하세요 : ";
			std::cin >> newKor;
			p[i]->setkor(newKor);

			int newMat;
			std::cout << "새로운 수학 성적을 입력하세요 : ";
			std::cin >> newMat;
			p[i]->setmat(newMat);

			int newEng;
			std::cout << "새로운 영어 성적을 입력하세요 : ";
			std::cin >> newEng;
			p[i]->seteng(newEng);
		}
		break;
	}
}

void StudentContainer::deleteTarget(const char* target)
{
	for (int i = 0; i < index; i++)
	{
		if (std::strcmp(target, p[i]->getName()) == 0) //학생이 존재한다면
		{
			std::cout << "'" << p[i]->getName() << "' 학생의 정보를 삭제합니다." << std::endl;
			delete p[i];

			index--;
			std::cout << "삭제가 완료되었습니다." << std::endl;
		}
		else
		{
			std::cout << "학생 '" << target << "'이(가) 존재하지 않습니다." << std::endl;
		}
	}
}
