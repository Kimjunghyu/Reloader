#pragma once
#include "GameObject.h"
#include "Enemy.h"

class Player;

class Spawner : public GameObject
{
protected:
	std::vector<Enemy::Types> enemyTypes;
	Player* player;

	sf::RenderWindow window;

	sf::Vector2f Pos;

	float interval = 1.f;
	int spawnCount = 3;

	float timer = 0.f;
	virtual GameObject* Create() = 0;
public:
	Spawner(const std::string& name = "");
	~Spawner() override = default;

	void Spawn();
	void Spawn(int count);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

};

