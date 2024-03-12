#pragma once
#include "GameObject.h"
#include "Enemy.h"
class Spawner : public GameObject
{
protected:
	std::vector<Enemy::Types> enemyTypes;
	
	float interval = 1.f;
	int spawnCount = 2;

	float timer = 0.f;
public:
	Spawner(const std::string& name = "");
	~Spawner() override = default;

	void Spawn();
	void Spawn(int count);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	GameObject* Create();
};

