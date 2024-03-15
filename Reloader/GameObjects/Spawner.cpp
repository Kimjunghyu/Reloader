#include "pch.h"
#include "Spawner.h"
#include "Player.h"

Spawner::Spawner(const std::string& name)
	: GameObject(name)
{
}

void Spawner::Spawn()
{
	auto size = FRAMEWORK.GetWindowSize();
	auto left = (sf::Vector2f)SCENE_MGR.GetCurrentScene()->ScreenToWorld({ 0, 0 });
	auto right = (sf::Vector2f)SCENE_MGR.GetCurrentScene()->ScreenToWorld({ size.x, 0 });
	sf::Vector2f newPos;

	if (Utils::RandomRange(0, 100) > 50)
	{
		newPos = right;
		newPos.x += 50.f;
	}
	else
	{
		newPos = left;
		newPos.x -= 50.f;
	}
	GameObject* newGo = Create();
	newGo->Init();
	newGo->Reset();
	newGo->SetPosition(newPos);
	SCENE_MGR.GetCurrentScene()->AddGo(newGo);
}

void Spawner::Spawn(int count)
{
	for (int i = 0; i < count; ++i)
	{
		Spawn();
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
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
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