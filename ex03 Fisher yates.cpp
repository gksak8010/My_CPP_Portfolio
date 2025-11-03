#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::cin;
using std::string;

#pragma warning (disable : 4996)

int main()
{
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (const int& el : a)
	{
		cout << a[0] << " ";
	}
	cout << endl;

	std::srand((unsigned int)std::time(NULL));
	//ÇÇ¼Å - ¿¹ÀÌÃ÷ ¼ÅÇÃ
	for (int i = 9; i > 0; i--)
	{
		int index = rand() % (i + 1);
		std::swap(a[i], a[index]);	//°ª ±³È¯
	}

	for (const int& el : a)
	{
		cout << a[0] << " ";
	}
	cout << endl;

	return 0;
}