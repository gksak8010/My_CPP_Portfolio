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

//캐릭터의 정보 저장 클래스
class Character
{
public:
	Character(string name = "unKnown", int x = 0, int y = 0, char icon = '?') : name(name), x(x), y(y), icon(icon)
	{
	}
	Character(const Character& other) : Character(other.name + "_clone", other.x, other.y, other.icon)	//생성자 호출
	{
	}
	void Move(char input, int width, int height)
	{
		switch (input)
		{
		case 'w': case 'W':
			if (y > 0)
				--y;
			break;
		case 's': case 'S':
			if (y < height - 1)
				++y;
			break;
		case 'a': case 'A':
			if (x > 0)
				--x;
			break;
		case 'd': case 'D':
			if (x < width - 1)
				++x;
			break;
		}
	}

	void Draw(char** map)
	{
		map[y][x] = icon;
	}

	inline int Getx() const { return x; }
	inline int Gety() const { return y; }
	inline string GetName() const { return name; }

private:
	int x, y;			//좌표(x: 행, y: 열)
	string name;	//캐릭터 이름
	char icon;		//몬스터: M, 히어로: H
};

//아이템 정보 저장 클래스---------------------------------------------------------
class Item
{
public:
	Item(int x = 0, int y = 0, char icon = 'I') : x(x), y(y), icon(icon), active(true)
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
	char icon;	//아이템: I
	bool active; //생존 여부
};

//게임 진행 클래스------------------------------------------------------------------
class GameManager
{
public:
	void setplayer(const Character& other)
	{
		player = other;
	}

public:
	GameManager() : score(0), monsterCount(MaxMonster)
	{
		//맵 생성(2차원 배열 생성)
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

		//몬스터 초기화
		int cIdx = 0;
		for (int i = 0; i < MaxMonster; i++)
		{
			//임시 객체 생성해서 대입
			monsters[i] = Character ("Monster_" + std::to_string(i + 1), position[cIdx].x, position[cIdx].y, 'M');
			monsterAlive[i] = true;
			++cIdx;
		}

		//아이템 초기화
		for (int i = 0; i < MaxItem; i++)
		{
			//임시 객체 생성해서 대입
			item[i] = Item(position[cIdx].x, position[cIdx].y);
			++cIdx;
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

				CheckMonster();	//몬스터와 충돌?
				CheckItem();		//아이템과 충돌?
			}
			if (monsterCount == 0)	//모든 몬스터를 제거했으면
			{
				SetMap();
				DisplayMap();
				cout << "\n\n\t\t축하합니다! 모든 몬스터를 제거했습니다.\n";
				cout << "\t\t획득한 점수는 [" << score << "]점 입니다.\n";
				return;
			}
		}
	}

private:
	void CheckMonster()
	{
		for (int i = 0; i < MaxMonster; i++)
		{
			if (monsterAlive[i])
			{
				if (monsters[i].Getx() == player.Getx() && monsters[i].Gety() == player.Gety())
				{
					score += 10;
					--monsterCount;
					monsterAlive[i] = false;
				}
			}
		}
	}
	void CheckItem()
	{
		for (int i = 0; i < MaxItem; i++)
		{
			if (item[i].IsActive())
			{
				if (item[i].Getx() == player.Getx() && item[i].Gety() == player.Gety())
				{
					score += 5;
					item[i].DeActivate();
				}
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

		//몬스터 표시
		for (int i = 0; i < MaxMonster; i++)
		{
			if (monsterAlive[i])
				monsters[i].Draw(map);
		}

		//아이템 표시
		for (int i = 0; i < MaxItem; i++)
		{
			item[i].Draw(map);
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

		cout << "\n\n점수:[" << score << "점 / 남은 몬스터: " << monsterCount << "]마리\n";
		cout << "w: 위, s: 아래, a: 왼쪽, d: 오른쪽, q: 종료\n";
	}

public:
	static const int Width = 20;
	static const int Hieight = 10;
	static const int MaxMonster = 5;
	static const int MaxItem = 3;

private:
	char** map;									//2차원 배열의 주소 저장
	Character monsters[MaxMonster];		//몬스터 5마리
	Character player;							//플레이어(히어로)
	Item item[MaxItem];						//아이템 3개
	bool monsterAlive[MaxMonster];		//몬스터 생존여부
	int monsterCount;							//살아있는 몬스터 개수
	int score = 0;								//몬스터: 10점, 아이템: 5점
};

int  main()
{
	Character h1("Hero_1", GameManager::Width/2, GameManager::Hieight/2, 'H');
	GameManager game;

	game.setplayer(h1);	//플레이어 등록
	game.Run();	//게임 시작


	return 0;
}