#include <iostream>
#include <math.h>
#include <vector>
#include <conio.h>
#include <fstream>
#include <string>


namespace game {

	class Entity;

	class Vector2 {

	private:
		float _x;
		float _y;


	public:

		float getX() {
			return _x;
		}
		void setX(float value) {
			_x = value;
		}
		float getY() {
			return _y;
		}
		void setY(float value) {
			_y = value;
		}

		Vector2() {
			_x = 0;
			_y = 0;
		}

		Vector2(float newX, float newY) {
			_x = newX;
			_y = newY;
		}

		friend bool operator!=(Vector2 lhs, Vector2 rhs) {
			if (lhs.getX() != rhs.getX() || lhs.getY() != rhs.getY()) {
				return true;
			}
			else {
				return false;
			}
		}

		friend bool operator==(Vector2 lhs, Vector2 rhs) {
			if (lhs.getX() == rhs.getX() || lhs.getY() == rhs.getY()) {
				return true;
			}
			else {
				return false;
			}
		}

		Vector2 operator+(Vector2 vecToAdd) {
			return Vector2(_x + vecToAdd.getX(), _y + vecToAdd.getY());
		}

		Vector2 operator-(Vector2 vecToSub) {
			return Vector2(_x - vecToSub.getX(), _y - vecToSub.getY());
		}

		Vector2 operator*(Vector2 vecToMul) {
			return Vector2(_x * vecToMul.getX(), _y * vecToMul.getY());
		}

		Vector2 operator*(float number) {
			return Vector2(_x * number, _y * number);
		}

		Vector2 operator/(Vector2 vecToDiv) {
			return Vector2(_x / vecToDiv.getX(), _y / vecToDiv.getY());
		}

		Vector2 operator/(float number) {
			return Vector2(_x / number, _y / number);
		}


		Vector2 div(float number) {
			return Vector2(_x / number, _y / number);
		}

		static Vector2 Zero() {
			return Vector2(0.0f, 0.0f);
		}
		static Vector2 One() {
			return Vector2(1.0f, 1.0f);
		}
		static Vector2 Up() {
			return Vector2(0.0f, -1.0f);
		}
		static Vector2 Right() {
			return Vector2(1.0f, 0.0f);
		}
		static Vector2 Null() {
			return Vector2(-1.0f, -1.0f);
		}
		void Set(const Vector2& original){
			_x = original._x;
			_y = original._y;
		}
		float Magnitude() {
			return sqrtf((_x * _x) + (_y * _y));
		}
		float SqrMagnitude() {
			return (_x * _x) + (_y * _y);
		}
		float Direction() {
			return atan(_y / _x);
		}
		Vector2 Normalize() {
			float m = this->Magnitude();

			if (m > 0) {
				return this->div(m);
			}
		}
		static float Distance(Vector2 vecOne, Vector2 vecTwo) {
			return fabsf(vecOne.Magnitude() - vecTwo.Magnitude());
		}
	};

	enum class NodeType { Passable, Impassable };

	class Node {
	public:
		Vector2 location;
		NodeType type;
		float travelCost;
		char asciiRep = 'l';
		char currAscii = 'l';

		Node() {
			location = Vector2();
			type = NodeType::Passable;
			travelCost = 1.0f;
			switch (type) {
			case NodeType::Passable:
				asciiRep = 'o';
				break;
			case NodeType::Impassable:
				asciiRep = '#';
				break;
			default:
				break;
			}
			currAscii = asciiRep;
		}

		Node(Vector2 positionToSpawn, NodeType spawnType) {
			location = positionToSpawn;
			type = spawnType;
			travelCost = 1.0f;
			switch (spawnType) {
			case NodeType::Passable:
				asciiRep = 'o';
				break;
			case NodeType::Impassable:
				asciiRep = '#';
				break;
			default:
				break;
			}
			currAscii = asciiRep;
		}

		Node(Vector2 positionToSpawn, NodeType spawnType, float initialCost) {
			location = positionToSpawn;
			type = spawnType;
			travelCost = initialCost;
			switch (spawnType) {
			case NodeType::Passable:
				asciiRep = 'o';
				break;
			case NodeType::Impassable:
				asciiRep = '#';
				break;
			default:
				break;
			}
			currAscii = asciiRep;
		}
	};

	class Map {
	private:
		int _sizeX;
		int _sizeY;
	public:

		std::vector<std::vector<Node>> gameMap;

		Map() {
			_sizeX = 0;
			_sizeY = 0;
		}

		Map(int sizeX, int sizeY) {
			_sizeX = sizeX;
			_sizeY = sizeY;
		}

		void Generate()
		{
			for (int i = 0; i < _sizeY; i++)
			{
				std::vector<Node> row;

				for (int j = 0; j < _sizeX; j++) {

					Node point(Vector2(j, i), NodeType::Passable);

					row.push_back(point);

				}

				gameMap.push_back(row);
			}
		}

		void LoadFromFileName(const std::string& filePath)
		{
			std::string line;

			std::fstream file(filePath);

			int xCord = 0;
			int yCord = 0;
			Node point;

			if (file)
			{
				while (std::getline(file, line))
				{
					std::vector<Node> row;
					for (char charVal : line) {
						switch (charVal) {

							case 'o':
								point = Node(Vector2(xCord, yCord), NodeType::Passable);
								break;
							case '#':
								point = Node(Vector2(xCord, yCord), NodeType::Impassable);
								break;
							default:
								point = Node(Vector2(xCord, yCord), NodeType::Passable);
								break;
						}
						row.push_back(point);
						xCord++;
					}
					gameMap.push_back(row);
					yCord++;
				}
				file.close();
				return;
			}

			file.close();
			return;
		}

		void UpdateAscii(Vector2 position, char asciiChar)
		{
			gameMap.at(position.getY()).at(position.getX()).currAscii = asciiChar;
		}

		void RevertAscii(Vector2 position) 
		{
			Node *referenceNode = &gameMap.at(position.getY()).at(position.getX());

			referenceNode->currAscii = referenceNode-> asciiRep;
		}

		void RevertAscii() {
			for(std::vector<Node> row : gameMap)
			{
				for (Node node : row) {
					node.currAscii = node.asciiRep;
				}
			}
		}

		void OutPutMap() {
			for (std::vector<Node> row : gameMap)
			{
				for (Node node : row) {
					std::cout << node.currAscii << " ";
				}
				std::cout << std::endl;
			}
		}
	};


	class Manager {
	private:
		static Manager* _instance;
		std::vector<Entity*> _entityList;
		Manager() {
			std::cout << "New Manager Created";
			std::vector<Entity*> newList;
			_entityList = newList;
		};

	public:

		static Manager* Instance() 
		{
			if (_instance == NULL) {
				_instance = new Manager;
			}
			return _instance; 
		}

		std::vector<Entity*> EntityList() { return _entityList; }

		void AddEntity(Entity& entityToAdd);

		void RemoveEntity(Entity& entityToRemove);

		Entity* GetEntityAtPos(Vector2 pos);
	};

	Manager* Manager::_instance = NULL;

	class Transform {
	public:
		Vector2 position;
	};

	class GameObject {
	public:
		Transform transform;
		char asciiRep;
	};

	class Entity : public GameObject {
	private:

	public:

		Map* mapPointer;
		int maxHealth;
		int health;
		int damage;
		int range;
		char attackRep;
		Vector2 previousAttackPos;

		void TakeDamage(Entity attacker) {
			health -= attacker.damage;
		}
		void TakeDamage(int value) {
			health -= value;
		}
		void Heal(int healValue) {
			health += healValue;
		}

		bool CheckMove(Vector2 newPosition) {
			try {
				if (mapPointer->gameMap.at(newPosition.getY()).at(newPosition.getX()).type != NodeType::Impassable) {
					return true;
				}
			}
			catch (...) {

			}
			return false;
		}

		void MoveTo(Vector2 newPosition) {
			if (CheckMove(newPosition)) {
				mapPointer->UpdateAscii(newPosition, asciiRep);
				mapPointer->RevertAscii(transform.position);
				transform.position = newPosition;
			}
		}

		void MoveUp() {
			Vector2 newPosition = transform.position + Vector2::Up();

			if (CheckMove(newPosition)) {
				mapPointer->UpdateAscii(newPosition, asciiRep);
				mapPointer->RevertAscii(transform.position);
 				transform.position = newPosition;
			}
		}

		void MoveDown() {
			Vector2 newPosition = transform.position - Vector2::Up();

			if (CheckMove(newPosition)) {
				mapPointer->UpdateAscii(newPosition, asciiRep);
				mapPointer->RevertAscii(transform.position);
				transform.position = newPosition;
			}
		}

		void MoveRight() {
			Vector2 newPosition = transform.position + Vector2::Right();

			if (CheckMove(newPosition)) {
				mapPointer->UpdateAscii(newPosition, asciiRep);
				mapPointer->RevertAscii(transform.position);
				transform.position = newPosition;
			}
		}

		void MoveLeft() {
			Vector2 newPosition = transform.position - Vector2::Right();

			if (CheckMove(newPosition)) {
				mapPointer->UpdateAscii(newPosition, asciiRep);
				mapPointer->RevertAscii(transform.position);
				transform.position = newPosition;
			}
		}

		void AttackUp() {
			Vector2 attackPosition = transform.position + Vector2::Up();

			if (CheckMove(attackPosition)) {
				previousAttackPos = attackPosition;

				Entity* attacked = Manager::Instance()->GetEntityAtPos(attackPosition);

				if (attacked != NULL) {
					attacked->TakeDamage(this->damage);
				}

				mapPointer->UpdateAscii(attackPosition, attackRep);
			}
		}
		void AttackDown() {
			Vector2 attackPosition = transform.position - Vector2::Up();

			if (CheckMove(attackPosition)) {
				previousAttackPos = attackPosition;

				Entity* attacked = Manager::Instance()->GetEntityAtPos(attackPosition);

				if (attacked != NULL) {
					attacked->TakeDamage(this->damage);
				}

				mapPointer->UpdateAscii(attackPosition, attackRep);
			}
		}
		void AttackRight() {
			Vector2 attackPosition = transform.position + Vector2::Right();

			if (CheckMove(attackPosition)) {
				previousAttackPos = attackPosition;

				Entity* attacked = Manager::Instance()->GetEntityAtPos(attackPosition);

				if (attacked != NULL) {
					attacked->TakeDamage(this->damage);
				}

				mapPointer->UpdateAscii(attackPosition, attackRep);
			}
		}
		void AttackLeft() {
			Vector2 attackPosition = transform.position - Vector2::Right();

			if (CheckMove(attackPosition)) {
				previousAttackPos = attackPosition;

				Entity* attacked = Manager::Instance()->GetEntityAtPos(attackPosition);

				if (attacked != NULL) {
					attacked->TakeDamage(this->damage);
				}

				mapPointer->UpdateAscii(attackPosition, attackRep);
			}
		}

		void OutputHealth() 
		{
			//std::cout << "Health: " << health << std::endl;
			for (int i = 0; i < maxHealth + 2; i++) {
				std::cout << '=';
			}
			std::cout << std::endl;
			std::cout << '=';
 			for (int i = 0; i < health; i++) {
				std::cout << '#';
			}
			for (int i = 0; i < maxHealth - health; i++) {
				std::cout << ' ';
			}
			std::cout << '=';
			std::cout << std::endl;
			for (int i = 0; i < maxHealth + 2; i++) {
				std::cout << '=';
			}
			std::cout << std::endl;
			std::cout << std::endl;
		}
	};

	class Player : public Entity {
	private:

	public:

		Player(Vector2 spawnLocation, Map& gameMap, int maxHealthValue) {
			mapPointer = &gameMap;
			transform.position = spawnLocation;
			maxHealth = maxHealthValue;
			health = maxHealthValue;
			asciiRep = '@';
			damage = 1;
			range = 1;
			mapPointer->UpdateAscii(transform.position, asciiRep);
			attackRep = '|';

			Manager::Instance()->AddEntity(*this);
		}
	};

	class Enemy : public Entity {

	public:

		Enemy(Vector2 spawnLocation, Map& gameMap, int maxHealthValue) {
			mapPointer = &gameMap;
			transform.position = spawnLocation;
			maxHealth = maxHealthValue;
			health = maxHealthValue;
			asciiRep = 'M';
			damage = 1;
			range = 1;
			mapPointer->UpdateAscii(transform.position, asciiRep);
			attackRep = '|';

			Manager::Instance()->AddEntity(*this);
		}
	};

	void Manager::AddEntity(Entity& entityToAdd) {
		_entityList.push_back(&entityToAdd);
	}

	void Manager::RemoveEntity(Entity& entityToRemove) {

		int index = 0;

		for (Entity* entity : _entityList) {

			if (entity == &entityToRemove) {
				break;
			}
			index++;
		}

		_entityList.erase(_entityList.begin() + index);
	}

	Entity* Manager::GetEntityAtPos(Vector2 pos) {

		for (Entity* entity : _entityList) {

			if (entity->transform.position == pos) {
				return entity;
			}

		}

		return NULL;

	}

	int GetInput()
	{
		int inputReturn;
		inputReturn = _getch();

		return inputReturn;
	}

}
