#include <iostream>
#include <string>
#include "ConsoleUtils.h"
#include <ctime>
#include <cstdlib>
#include <conio.h> //_kbhit, _getch() : 에코기능x

using std::cout;
using std::endl;
using std::cin;
using std::string;

#pragma warning (disable : 4996)

class Character		//캐릭터 정보 저장
{
public:
	Character(string name = "unKnown", int x = 0, int y = 0, char icon = '?') : name(name), x(x), y(y), icon(icon)
	{
	}
	Character(const Character& other) : Character(other.name + "_clone", other.x, other.y, other.icon)
	{
	}
	void Move(char input, int width, int height)
	{
		switch (input)
		{
		case 'w': case 'W':
			if (y > 0)
				--y;
			++count;
			break;
		case 's': case 'S':
			if (y < height - 1)
				++y;
			++count;
			break;
		case 'a': case 'A':
			if (x > 0)
				--x;
			++count;
			break;
		case 'd': case 'D':
			if (x < width - 1)
				++x;
			++count;
			break;
		}
	}

	void Draw(char** map)
	{
		map[y][x] = icon;
	}
	inline int MoveCount() const { return count; }
	inline int Getx() const { return x; }
	inline int Gety() const { return y; }
	inline string GetName() const { return name; }
private:
	int x, y;			//좌표
	char icon;		//플레이어: P
	string name;	//캐릭터 이름
	int count;		//이동한 횟수
};

class Hurdle
{
public:
	Hurdle(int x = 0, int y = 0, char icon = 'I') : x(x), y(y), icon(icon), active(true)
	{
	}

	inline int Getx() const { return x; }
	inline int Gety() const { return y; }
	inline bool IsActive() const { return active; }
	void DeActivate() { active = false; }
	void Draw(char** map)
	{
		if (active)
			map[y][x] = icon;
	}
private:
	int x, y;		//좌표
	char icon;	//장애물: O
	bool active;	//장애물에 걸리면 장애물은 없어짐 + 목숨이 깎임.
};

class GameManager
{
public:
	void setplayer(const Character& other)
	{
		player = other;
	}

public:
	GameManager() : score(0), AllMoveCount(0)
	{
		map = new char* [Hieight];	//포인터 배열 생성
		for (int i = 0; i < Hieight; i++)
		{
			map[i] = new char[Width];
		}
		//좌표 저장하기 위한 구조체 생성
		struct point { int x, y; };
		point position[Width * Hieight - 1];	//좌표를 저장하기 위한 배열 선언

		//구조체 변수에 차례대로 좌표 저장
		int index = 0;
		for (int i = 0; i < Hieight; i++)	//행 좌표
		{
			for (int j = 0; j < Width; j++)	//열 좌표
			{
				if (i == Hieight / 2 && j == Width / 2) //중앙좌표 값
				{
					continue;
				}
				position[index].x = j;
				position[index].y = i;
				++index;
			}

		}
		//피셔 - 에이츠 셔플 방식으로 좌표 섞기
		std::srand((unsigned int)time(NULL));
		for (int i = index - 1; i > 0; i--)
		{
			int index = std::rand() % (i + 1);
			std::swap(position[i], position[index]);
		}

		//장애물 초기화
		int index = 0;
		for (int i = 0; i < Maxhurdle; i++)
		{
			hurdle[i] = Hurdle(position[index].x, position[index].y);
			++index;
		}
	}
	~GameManager()
	{
		for (int i = 0; i < Hieight; i++)
		{
			delete[] map[i];
		}
		cout << "2차원 맵 제거(" << Hieight << " *  " << Width << ")제거\n";

		delete[] map;
		cout << "2차원 배열의 포인터 제거\n";
	}

	void Run()
	{
		while (true)
		{
			HideCursor();
			//맵 설정
			SetMap();
			DisplayMap();

			if (_kbhit())	//키보드 입력이 있었다면?
			{
				char input = _getch();		//입력 받은 값을 저장

				if (input == 'q')
					return;	//함수 종료

				player.Move(input, Width, Hieight);

				CheckHurdle();		//아이템과 충돌?
			}
		}
	}

	void SetMap()
	{
		//맵을 '.'으로 초기화
		for (int i = 0; i < Hieight; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				map[i][j] = '.';
			}
		}

		//아이템 표시
		for (int i = 0; i < Maxhurdle; i++)
		{
			hurdle[i].Draw(map);
		}

		//플레이어 표시
		player.Draw(map);
	}

	void DisplayMap()
	{
		GotoXY(0, 0);
		for (int i = 0; i < Hieight; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				cout << map[i][j];
			}
			cout << endl;
		}

		cout << "w: 위, s: 아래, a: 왼쪽, d: 오른쪽, q: 종료\n";
		cout << "\n\n남은 이동 가능 횟수 : [" << AllMoveCount - MoveCount() << "]\n";
	}

public:
	static const int Maxhurdle = 10;
	static const int Width = 20;
	static const int Hieight = 5;
	static const int AllMoveCount = 30;			//총 이동 가능 횟수
private:
	char** map;
	Character player;					//플레이어
	Hurdle hurdle[Maxhurdle];		//장애물(10개)
	bool hurdleAlive[Maxhurdle];	//허들 생존여부
	int score = 0;						//(총 이동 가능 횟수 - 이동한 횟수) * 10
};

int main()
{

	return 0;
}