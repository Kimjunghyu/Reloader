#include "pch.h"
#include "EnemySpwaner.h"

EnemySpwaner::EnemySpwaner(const std::string& name)
	:Spawner(name)
{
}

GameObject* EnemySpwaner::Create()
{
	Enemy::Types enemyType = enemyTypes[Utils::RandomRange(0, enemyTypes.size())];
	return Enemy::Create(enemyType);
}

void EnemySpwaner::Reset()
{
	Spawner::Reset();

	enemyTypes.clear();
	enemyTypes.push_back(Enemy::Types::Distance);
	enemyTypes.push_back(Enemy::Types::Distance);
	enemyTypes.push_back(Enemy::Types::Melee);
}
