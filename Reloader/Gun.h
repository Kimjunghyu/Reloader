#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class SceneGame;

class Gun : public SpriteGo
{
protected:
	Animator animator;
	SceneGame* sceneGame;

	float gravity = 500.f;
	float speed = 400.f;
	sf::Vector2f pos;
	bool isFiring = false;
	int bullet = 6;
public:
	Gun(const std::string& name = "");
	~Gun()override;
	void TestInstance();
	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	
	bool GetisFiring(bool isFiring) { return isFiring; }
};

