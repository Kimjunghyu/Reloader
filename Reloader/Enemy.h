#pragma once
#include "SpriteGo.h"
#include "TextGo.h"

class Player;

class Enemy : public SpriteGo
{
public:
	enum class Types
	{
		Distance,
		Melee,
	};
	static const int TotalTypes = 2;
	static Enemy* Create(Types enemyTypes);

protected:
	Types type;

	sf::Vector2f direction = { 0.f,0.f };

	Player* player = nullptr;
	int hp = 100;
	float speed = 100.f;

	TextGo* textMsg;
	float timer;
	int concentration;
public:
	Enemy(const std::string& name = "");
	~Enemy() override = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

	void Draw(sf::RenderWindow& window)override;
	void Onhit(int d);

	void EnemyHpSet(int h) { hp = h; }
	void SetConcent(int i) { concentration = i; }
};

