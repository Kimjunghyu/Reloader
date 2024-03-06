#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class SceneGame;

class Gun : public SpriteGo
{
protected:
	Animator animator;
	SceneGame* sceneGame;
	SpriteGo* bullet;

	float gravity = 500.f;
	float speed = 400.f;
	sf::Vector2f pos;
	bool isFiring = false;
	int bulletCount = 6;
	float timer = 0.f;
	float fireinterval = 0.5f;
	sf::Vector2f bulletFiring = { 1.f,-1.f };
	sf::Vector2f Direction = { 1.f, 1.f };
	sf::Vector2f bulletPos;
public:
	Gun(const std::string& name = "");
	~Gun()override;
	void TestInstance();
	void EmptyMagazine();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	
	bool GetisFiring(bool isFiring) { return isFiring; }
	int GetBulletCount() { return bulletCount; }
};

