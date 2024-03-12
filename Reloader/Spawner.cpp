#include "pch.h"
#include "Spawner.h"

Spawner::Spawner(const std::string& name)
	: GameObject(name)
{
}

void Spawner::Spawn()
{
	sf::Vector2f pos = position + Utils::RandomOnUnitCircle();

	GameObject* newGo = Create();
	newGo->Init();
	newGo->Reset();
	newGo->SetPosition(pos);
	SCENE_MGR.GetCurrentScene()->AddGo(newGo);
}

void Spawner::Spawn(int count)
{
	for (int i = 0; i < count; ++i)
	{
		Spawn(count);
	}
}

void Spawner::Init()
{
	GameObject::Init();
}

void Spawner::Release()
{
	GameObject::Release();
}

void Spawner::Reset()
{
	GameObject::Reset();

	interval = 1.f;
	spawnCount = 1;

	timer = 0.f;
}

void Spawner::Update(float dt)
{
	GameObject::Update(dt);

	timer += dt;
	if (timer > interval)
	{
		timer = 0.f;
		Spawn(spawnCount);
	}
}

GameObject* Spawner::Create()
{
	Enemy::Types enemyType = enemyTypes[Utils::RandomRange(0, enemyTypes.size())];
	return Enemy::Create(enemyType);
}
