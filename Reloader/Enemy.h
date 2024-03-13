#pragma once
#include "SpriteGo.h"
#include "TextGo.h"

class Player;
class EnemySpwaner;
class SceneGame;

class Enemy : public SpriteGo
{
public:
	enum class Types
	{
		Distance,
		Melee,
	};
	static const int TotalTypes = 2;
	static Enemy* Create(Types enemyType);

protected:
	Types type;
	EnemySpwaner* enemySpawner;
	SceneGame* sceneGame;
	sf::RenderWindow window;

	sf::Vector2f direction = { 0.f,0.f };
	sf::Vector2f enemyPos = { 0.f,0.f };

	Player* player = nullptr;
	int hp = 100;
	float speed = 100.f;
	float range = 0.f;

	TextGo* textMsg;
	float timer;
	int concentration;
	bool ondie = false;
public:
	Enemy(const std::string& name = "");
	~Enemy() override = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

	void Draw(sf::RenderWindow& window)override;
	void Onhit(int d);
	void OnDie();

	void EnemyHpSet(int h) { hp = h; }
	void SetConcent(int i) { concentration = i; }
};

