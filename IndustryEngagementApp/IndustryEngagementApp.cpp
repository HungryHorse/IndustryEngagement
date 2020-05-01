// IndustryEngagementApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <map>
#include "GameInfo.cpp"
using namespace game;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESCAPE_KEY 27
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100

int main()
{
	Manager::Instance();

	std::vector<Enemy*> enemyObjects;

	std::map<std::string, std::string> mapDictionary = {
		{"MapOne", "map.txt"}
	};

	Map gMap;
	//gMap.Generate();
	gMap.LoadFromFileName(mapDictionary.find("MapOne")->second);
	 
   	Player* player = new Player({1,1}, gMap, 10);
	Enemy* enemy = new Enemy({1,7}, gMap, 10);

	enemyObjects.push_back(enemy);


	int input;
	int counter = 0;
	bool gamePlaying = true;

	//GameLoop
	do {

		counter++;

		system("CLS");

		if (player->previousAttackPos != Vector2::Null() && player->transform.position != player->previousAttackPos && counter > 1)
		{
			gMap.RevertAscii(player->previousAttackPos);
			player->previousAttackPos = Vector2::Null();
		}

		player->OutputHealth();
		gMap.OutPutMap();

		enemy->OutputHealth();

		input = GetInput();

		switch (input)
		{
			case KEY_W:
				player->MoveUp();
				break;
			case KEY_A:
				player->MoveLeft();
				break;
			case KEY_S:
				player->MoveDown();
				break;
			case KEY_D:
				player->MoveRight();
				break;
			case KEY_UP:
				player->AttackUp();
				counter = 0;
				break;
			case KEY_DOWN:
				player->AttackDown();
				counter = 0;
				break;
			case KEY_LEFT:
				player->AttackLeft();
				counter = 0;
				break;
			case KEY_RIGHT:
				player->AttackRight();
				counter = 0;
				break;
			case ESCAPE_KEY:
				gamePlaying = false;
				break;
			default:
				break;
		}

		int entityPos = 0;
		for (Enemy* enemy : enemyObjects) {
			if (Manager::Instance()->GetEntityByName(enemy->entityName) == NULL) {
				enemyObjects.erase(enemyObjects.begin() + entityPos);
				delete enemy;
			}
			else
			{
				enemy->NextMove(player->transform.position);
			}

			entityPos++;
		}

	} while (gamePlaying);
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
