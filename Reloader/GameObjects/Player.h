#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class SceneGame;
class UiMsg;
class Enemy;
class Spawner;
class UiHud;

class Player : public SpriteGo
{
protected:
	Animator animator;
	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f look = { 1.0f, 0.f };
	float speed = 200.f;

	sf::Vector2f armPos;
	sf::Vector2f gunPos;
	SpriteGo* playerArm;
	SpriteGo* playerGun;
	UiMsg* uiMsg;
	Enemy* enemy;
	UiHud* uiHud;

	std::vector<Spawner*> enemySpawners;
	std::list<GameObject*> enemyList;

	int hp = 100;
	int maxHp = 100;
	int enemyBulletCount = 0;

	float timer = 0.f;
	float maxConcent = 100.f;

	SceneGame* sceneGame = nullptr;
	bool moveArm = false;
	bool playerMove = true;
	bool isAlive = true;
	bool noDamage = false;
	bool addMagazine = false;
public:
	Player(const std::string& name = "");
	~Player() override = default;

	const std::list<GameObject*>& GetEnemyList() const { return enemyList; }

	SpriteGo* GetPlayerArm()
	{
		return playerArm;
	}

	void TestInstance();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	bool SetMoveArm(bool c) { return moveArm = c; }
	void SetPlayerArmAngle(sf::Vector2f v);
	bool playerSit = false;
	void AddMagazine(bool b) { addMagazine = b; }

	int GetHp() { return hp; }
	void SetHp(int i) { hp = i; }

	void Onhit(int i);
	void OnDie();
};

