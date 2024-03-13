#pragma once
#include "Spawner.h"
#include "Enemy.h"

class EnemySpwaner : public Spawner
{
protected:
	std::vector<Enemy::Types> enemyTypes;

public:
	EnemySpwaner(const std::string& name = "");
	~EnemySpwaner() override = default;

	GameObject* Create() override;
	void Reset() override;
};

