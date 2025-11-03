#pragma once
#include "Student.h"

class StudentContainer
{
public:
	//학생추가
	void addStudent(const char* Name, int Grade, int Class, int kor, int mat, int eng);
	//모든 학생정보 보이기
	void displayAllStudentInfo() const;
	void targetStudent(const char* target);
	void modifyTarget(const char* target);
	void deleteTarget(const char* target);

public:
	~StudentContainer()
	{
		for (int i = 0; i < index; i++)
		{
			delete p[i];
		}
		index = 0;
	}


private:
	//저장 가능한 학생수
	static const int STUDENT_SIZE = 100;
	Student* p[STUDENT_SIZE] = { nullptr };
	int index;
};