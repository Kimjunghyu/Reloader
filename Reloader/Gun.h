#pragma once
#include "SpriteGo.h"
#include "Animator.h"
#include "Player.h"

class SceneGame;
class Effect;
class UiMsg;
class UiHud;

class Gun : public SpriteGo
{
protected:
	Animator animator;
	SceneGame* sceneGame;
	SpriteGo* bullet;

	Player* player;
	Effect* effect = nullptr;
	UiMsg* uiMsg;
	UiHud* uiHud;

	float gravity = 500.f;
	float speed = 400.f;
	sf::Vector2f pos;

	int bulletCount = 6;
	int getBullet = 0;
	float timer = 0.f;
	float fireinterval = 0.5f;

	sf::Vector2f bulletFiring = { 1.f,-1.f };
	sf::Vector2f Direction = { 1.f, 1.f };
	sf::Vector2f bulletPos;

	bool reloaded = false;
	bool isFiring = false;
	bool anistop = false;
	bool missFire = false;
	bool onTarget = false;
	bool onMagazine = true;
public:
	Gun(const std::string& name = "");
	~Gun()override;
	void TestInstance();
	void MissFire();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	
	bool GetisFiring(bool isFiring) { return isFiring; }
	int GetBulletCount() { return bulletCount; }

	bool GetOnTarget() { return onTarget; }
};

