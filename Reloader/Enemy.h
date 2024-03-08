#pragma once
#include "SpriteGo.h"
#include "TextGo.h"

class Player;

class Enemy : public SpriteGo
{
protected:
	Player* player = nullptr;
	int hp = 100;

	TextGo* textMsg;
	float timer;
public:
	Enemy(const std::string& name = "");
	~Enemy() override = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

	void Draw(sf::RenderWindow& window)override;
	void Onhit(int d);

	void EnemyHpSet(int h) { hp = h; }
};

