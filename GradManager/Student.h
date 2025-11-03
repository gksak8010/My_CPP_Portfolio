#pragma once

class Student
{
public:
	void displayStudentInfo();
	double evg(int kor, int mat, int eng);

public:
	Student();
	Student(const char* Name, int Grade, int Class, int score);
	Student(const Student& other);
	~Student();

public:
	inline const char* getName() const { return Name; }
	inline const int getGrade() const { return Grade; }
	inline const int getClass() const { return Class; }
	inline const int getkor() const { return kor; }
	inline const int getmat() const { return mat; }
	inline const int geteng() const { return eng; }

	void setName(const char* Name);
	inline void setGrade(int Grade) { this->Grade = Grade; }
	inline void setClass(int Class) { this->Class = Class; }
	inline void setkor(int kor) { this->kor = kor; }
	inline void setmat(int mat) { this->mat = mat; }
	inline void seteng(int eng) { this->eng = eng; }

private:
	char* Name = nullptr;
	int Grade = 0;
	int Class = 0;
	int kor = 0;
	int mat = 0;
	int eng = 0;
};