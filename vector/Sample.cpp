#include <iostream>
#include <vector>

//class Enemy
//{
//public:
//	Enemy();
//	~Enemy();
//
//private:
//
//};

int main()
{
	//Enemy enemy;
	
	//ベクターを宣言
	std::vector<int> number;
	std::vector<float> number2;
	//std::vector<Enemy> enemies;

	number.push_back(10);
	number.push_back(20);
	number.push_back(30);

	std::cout << number.size() << std::endl;

	int num = number[0];
	std::cout << num ;
	//削除
	number.clear();
	return 0;
}