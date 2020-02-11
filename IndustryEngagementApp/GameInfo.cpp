#include <math.h>
#include <vector>

namespace game {

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
			return Vector2(0.0f, 1.0f);
		}
		static Vector2 Right() {
			return Vector2(1.0f, 0.0f);
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


	enum NodeType { Passable, Impassable };

	class Node {
	public:
		Vector2 location;
		NodeType type;
		float travelCost;
		char asciiRep;
		char currAscii;

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

		Map(int sizeX, int sizeY) {
			_sizeX = sizeX;
			_sizeY = sizeY;
		}

		void Generate()
		{
			for (int i = 0; i < _sizeY; i++)
			{
				for (int j = 0; j < _sizeX; i++) {

					gameMap[j][i] = Node(Vector2(j, i), NodeType::Passable);

				}
			}
		}
	};

	class Transform {
	public:
		Vector2 position;
	};

	class GameObject {
	public:
		Transform transform;
	};
}