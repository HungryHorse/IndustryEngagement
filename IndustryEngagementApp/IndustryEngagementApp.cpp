// IndustryEngagementApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameInfo.cpp"
using namespace game;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main()
{
    Vector2 oneRight(1,1);
	Vector2& rOneRight = oneRight;
    Vector2 twoRight = rOneRight + Vector2::Right();

	Map gMap(4, 4);
	gMap.Generate();
	 
   	Player player({0,0}, gMap);

	player.MoveUp();
	player.MoveLeft();
	player.MoveRight();

	int input;
	int counter = 0;

	//GameLoop
	do {

		counter++;

		system("CLS");

		if (player.previousAttackPos != Vector2::Null() && player.transform.position != player.previousAttackPos && counter > 1)
		{
			gMap.RevertAscii(player.previousAttackPos);
			player.previousAttackPos = Vector2::Null();
		}

		gMap.OutPutMap();

		input = GetInput();

		switch (input)
		{
			case 119:
				player.MoveUp();
				break;
			case 97:
				player.MoveLeft();
				break;
			case 115:
				player.MoveDown();
				break;
			case 100:
				player.MoveRight();
				break;
			case KEY_UP:
				player.AttackUp();
				counter = 0;
				break;
			case KEY_DOWN:
				player.AttackDown();
				counter = 0;
				break;
			case KEY_LEFT:
				player.AttackLeft();
				counter = 0;
				break;
			case KEY_RIGHT:
				player.AttackRight();
				counter = 0;
				break;
			default:
				break;
		}

	} while (true);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
