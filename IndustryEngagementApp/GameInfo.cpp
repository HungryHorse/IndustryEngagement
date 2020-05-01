#include <iostream>
#include <math.h>
#include <vector>
#include <conio.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <boost/ptr_container/ptr_vector.hpp>


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
			if (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY()) {
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

		Vector2 operator-() {
			return Vector2(-_x, -_y);
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
		boost::ptr_vector<Vector2> neighbourLocations;
		int dist = 2147483647;
		std::vector<Node> prev;

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

		static int Distance(Node primaryNode, Node secondaryNode) {
			if ((primaryNode.type == NodeType::Impassable || secondaryNode.type == NodeType::Impassable) || (secondaryNode.currAscii != secondaryNode.asciiRep)) {
				return 2147483647;
			}
			else {
				return 1;
			}
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

		int Area() {
			return _sizeX * _sizeY;
		}

		int SizeX() {
			return _sizeX;
		}

		int SizeY() {
			return _sizeY;
		}

		void Generate()
		{

			for (int i = 0; i < _sizeY; i++)
			{
				std::vector<Node> row;

				for (int j = 0; j < _sizeX; j++) {

					Node* point = new Node(Vector2(j, i), NodeType::Passable);

					row.push_back(*point);
				}

				gameMap.push_back(row);
			}

			ConnectGraph();
		}

		void ConnectGraph() {

			for (int i = 0; i < _sizeY; i++)
			{
				for (int j = 0; j < _sizeX; j++) {

					if (i > 0) {
						Node* pointOne = &gameMap[i-1][j];
						Node* pointTwo = &gameMap[i][j];
						pointOne->neighbourLocations.push_back(&pointTwo->location);
						pointTwo->neighbourLocations.push_back(&pointOne->location);
					}
					if (j > 0) {
						Node* pointOne = &gameMap[i][j-1];
						Node* pointTwo = &gameMap[i][j];
						pointOne->neighbourLocations.push_back(&pointTwo->location);
						pointTwo->neighbourLocations.push_back(&pointOne->location);
					}
				}
			}

		}

		void LoadFromFileName(const std::string& filePath)
		{
			std::string line;

			std::fstream file(filePath);

			int xCord = 0;
			int yCord = 0;
			Node* point;

			if (file)
			{
				while (std::getline(file, line))
				{
					std::vector<Node> row;
					for (char charVal : line) {
						switch (charVal) {
							case 'o':
								point = new Node(Vector2(xCord, yCord), NodeType::Passable);
								break;
							case '#':
								point = new Node(Vector2(xCord, yCord), NodeType::Impassable);
								break;
							default:
								point = new Node(Vector2(xCord, yCord), NodeType::Passable);
								break;
						}

						row.push_back(*point);
						xCord++;
					}
					gameMap.push_back(row);
					xCord = 0;
					yCord++;
				}
				_sizeY = gameMap.size();
				_sizeX = gameMap[0].size();
				ConnectGraph();
				file.close();
				return;
			}

			file.close();
			return;
		}

		void UpdateAscii(Vector2 position, char asciiChar)
		{
			Node* referenceNode = &gameMap.at(position.getY()).at(position.getX());

			referenceNode->currAscii = asciiChar;
		}

		void RevertAscii(Vector2 position) 
		{
			Node *referenceNode = &gameMap.at(position.getY()).at(position.getX());

			referenceNode->currAscii = referenceNode-> asciiRep;
		}

		void RevertAscii() {

			for (int i = 0; i < _sizeY; i++)
			{
				for (int j = 0; j < _sizeX; j++) {

					if (i > 0) {
						Node* point = &gameMap[i][j];
						point->currAscii = point->asciiRep;
					}
				}
			}
		}

		void OutPutMap() {
			for (int i = 0; i < _sizeY; i++)
			{
				for (int j = 0; j < _sizeX; j++) {
					Node* point = &gameMap[i][j];
					std::cout << point->currAscii << " ";
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

		Entity* GetEntityByName(std::string entityName);

		Node Pathfinding(Vector2 source, Vector2 target, Map& graph);
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
		std::string entityName;
		int maxHealth;
		int health;
		int damage;
		int range;
		char attackRep;
		Vector2 previousAttackPos;

		virtual ~Entity() {
			std::cout << "Entity " << entityName << " Has been destroyed \n";
		}

		void TakeDamage(Entity attacker) {
			health -= attacker.damage;
			if (health <= 0) {
				Die();
			}
		}
		void TakeDamage(int value) {
			health -= value;
			if (health <= 0) {
				Die();
			}
		}
		void Heal(int healValue) {
			health += healValue;
			if (health > maxHealth) {
				health = maxHealth;
			}
		}

		void Die() {
			mapPointer->RevertAscii(transform.position);
			Manager::Instance()->RemoveEntity(*this);
		}

		bool CheckMove(Vector2 newPosition) {

			Node* nodeAtPos = &mapPointer->gameMap.at(newPosition.getY()).at(newPosition.getX());

			try {
				if (nodeAtPos->type != NodeType::Impassable && nodeAtPos->currAscii != 'M') {
					return true;
				}
			}
			catch (...) {

			}
			return false;
		}

		bool CheckAttack(Vector2 attackPosition) {
			try {
				if (mapPointer->gameMap.at(attackPosition.getY()).at(attackPosition.getX()).type != NodeType::Impassable) {
					return true;
				}
			}
			catch (...) {

			}
			return false;
		}

		int KnockBack(int strength, Vector2 direction) {
			
			int count = 1;
			for (count; count <= strength; count++) {
				if (CheckMove(transform.position + direction * count)) {
					mapPointer->UpdateAscii(transform.position + direction * count, asciiRep);
					mapPointer->RevertAscii(transform.position);
					transform.position = transform.position + direction * count;

					return count;
				}
				if (count == 1) {
					return 0;
				}
			}
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
			int distance = -1;

			if (CheckAttack(attackPosition)) {
				previousAttackPos = attackPosition;

				Entity* attacked = Manager::Instance()->GetEntityAtPos(attackPosition);

				if (attacked != NULL) {
					attacked->TakeDamage(this->damage);
					distance = attacked->KnockBack(1, Vector2::Up());
				}

				if (distance != 0) {
					mapPointer->UpdateAscii(attackPosition, attackRep);
				}
				else {
					previousAttackPos = Vector2::Null();
				}
			}
		}
		void AttackDown() {
			Vector2 attackPosition = transform.position - Vector2::Up();
			int distance = -1;

			if (CheckAttack(attackPosition)) {
				previousAttackPos = attackPosition;

				Entity* attacked = Manager::Instance()->GetEntityAtPos(attackPosition);

				if (attacked != NULL) {
					attacked->TakeDamage(this->damage);
					distance = attacked->KnockBack(1, -Vector2::Up());
				}

				if (distance != 0) {
					mapPointer->UpdateAscii(attackPosition, attackRep);
				}
				else {
					previousAttackPos = Vector2::Null();
				}
			}
		}
		void AttackRight() {
			Vector2 attackPosition = transform.position + Vector2::Right();
			int distance = -1;

			if (CheckAttack(attackPosition)) {
				previousAttackPos = attackPosition;

				Entity* attacked = Manager::Instance()->GetEntityAtPos(attackPosition);

				if (attacked != NULL) {
					attacked->TakeDamage(this->damage);
					distance = attacked->KnockBack(1, Vector2::Right());
				}

				if (distance != 0) {
					mapPointer->UpdateAscii(attackPosition, attackRep);
				}
				else {
					previousAttackPos = Vector2::Null();
				}
			}
		}
		void AttackLeft() {
			Vector2 attackPosition = transform.position - Vector2::Right();
			int distance = -1;

			if (CheckAttack(attackPosition)) {
				previousAttackPos = attackPosition;

				Entity* attacked = Manager::Instance()->GetEntityAtPos(attackPosition);

				if (attacked != NULL) {
					attacked->TakeDamage(this->damage);
					distance = attacked->KnockBack(1, -Vector2::Right());
				}

				if (distance != 0) {
					mapPointer->UpdateAscii(attackPosition, attackRep);
				}
				else {
					previousAttackPos = Vector2::Null();
				}
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
			entityName = "Player";
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
			entityName = "Enemy";
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

		void NextMove(Vector2 targetLocation) {
			Node target = Manager::Instance()->Pathfinding(transform.position, targetLocation, *mapPointer);

			if (target.location == Vector2(-1, -1)) {
				return;
			}

			std::vector<Node> moveSequence;
			Node u = target;

			while (true)
			{
				if (u.location != transform.position && u.prev.size() > 0) {
					moveSequence.push_back(u);
					u = u.prev[0];
				}
				else {
					break;
				}
			}

			Vector2 newPosition = moveSequence.at(moveSequence.size() - 1).location;

			mapPointer->UpdateAscii(newPosition, asciiRep);
			mapPointer->RevertAscii(transform.position);
			transform.position = newPosition;
		}
	};

	void Manager::AddEntity(Entity& entityToAdd) {
		entityToAdd.entityName += std::to_string(_entityList.size());
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

	Entity* Manager::GetEntityByName(std::string entityName) {

		for (Entity* entity : _entityList) {

			if (entity->entityName == entityName) {
				return entity;
			}

		}
		
		return NULL;
	}

	int GetIndexFromLocation(std::vector<Node>& vectors, Vector2 vectorToFind) {

		for (int i = 0; i < vectors.size(); i++) {
			if (vectors[i].location == vectorToFind) {
				return i;
			}
		}

	}

	int GetSmallestDist(std::vector<Node>& dist)
	{
		int shorestDist = dist.at(0).dist;
		int location = 0;

		for (int i = 0; i < dist.size(); i++) {
			if (shorestDist > dist.at(i).dist) {
				shorestDist = dist.at(i).dist;
				location = i;
			}
		}

		return location;
	}

	Node Manager::Pathfinding(Vector2 source, Vector2 target, Map& graph) {
		Map* graphP = &graph;

		std::vector<Node> vertexSet;

		for (int i = 0; i < graphP->gameMap.size(); i++)
		{
			for (int j = 0; j < graphP->gameMap[0].size(); j++) {
				Node nodeReference = graphP->gameMap.at(i).at(j);
				vertexSet.push_back(nodeReference);
			}
		}

		vertexSet.at(GetIndexFromLocation(vertexSet, source)).dist = 0;

		while (vertexSet.size() > 0) {

			int nodeLocation = GetSmallestDist(vertexSet);
			Node u = vertexSet.at(nodeLocation);

			vertexSet.erase(vertexSet.begin() + nodeLocation);

			if (u.location == target) {
				return u;
			}

			for (int i = 0; i < u.neighbourLocations.size(); i++) {
				try {
					int alt = u.dist + Node::Distance(u, vertexSet.at(GetIndexFromLocation(vertexSet, u.neighbourLocations[i])));

					Node& vNode = vertexSet.at(GetIndexFromLocation(vertexSet, u.neighbourLocations[i]));

					if (alt < vNode.dist) {
						vNode.dist = alt;
						if (vNode.prev.size() != 0) {
							vNode.prev[0] = u;
						}
						else {
							vNode.prev.push_back(u);
						}
					}
				}
				catch(...){

				}
			}
		}

		return Node(Vector2(-1,-1), NodeType::Impassable);
	}

	int GetInput()
	{
		int inputReturn;
		inputReturn = _getch();

		return inputReturn;
	}

}
