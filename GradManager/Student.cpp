#include "Student.h"
#include <cstring>
#include <iostream>

#pragma warning (disable:4996)

void Student::displayStudentInfo()
{
	//학생정보 출력
	std::cout << "[학생명 : " << Name << "학년 : " << Grade << "반 : " << Class << "국어: " << kor << "수학 : " << mat << "영어 : " << eng << "평군 : " << evg << "]\n";
}

double Student::evg(int kor, int mat, int eng)
{
	double evg = 0;
	evg = (kor + mat + eng) / 3;

	return evg;
}

Student::Student()
{
	//학생이름: Unknown, 학년 : 0, 반 : 0, 국어 : 0, 수학 : 0, 영어 : 0으로 초기화
	Name = new char[8];
	strcpy(Name, "Unknown");

	Grade = 0;
	Class = 0;
	kor = 0;
	mat = 0;
	eng = 0;
}

Student::Student(const char* Name, int Grade, int Class, int score)
{
	this->Name = new char[std::strlen(Name) + 1];
	std::strcpy(this->Name, Name);
	
	this->Grade = Grade;

	this->Class = Class;

	this->kor = kor;

	this->mat = mat;

	this->eng = eng;
}

Student::Student(const Student& other) : Student(other.Name, other.Grade, other.Class, other.kor, other.mat, other.eng)
{
}

Student::~Student()
{
}

void Student::setName(const char* Name)
{
	if (this->Name != nullptr)
		delete[] this->Name;

	this->Name = new char[std::strlen(Name) + 1];
	strncpy(this->Name, Name, strlen(Name) + 1);
}
