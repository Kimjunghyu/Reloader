#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class SceneGame;

class Player : public SpriteGo
{
protected:
	Animator animator;
	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f look = { 1.0f, 0.f };
	float speed = 200.f;

	sf::Vector2f armPos;
	SpriteGo* playerArm;

	SceneGame* sceneGame = nullptr;
	bool moveArm = false;
public:
	Player(const std::string& name = "");
	~Player() override = default;

	SpriteGo* GetPlayerArm()
	{
		return playerArm;
	}

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	bool SetMoveArm(bool c) { return moveArm = c; }
	void SetPlayerArmAngle(sf::Vector2f v);
};

