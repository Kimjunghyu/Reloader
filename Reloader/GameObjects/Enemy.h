#pragma once
#include "SpriteGo.h"
#include "TextGo.h"
#include "Animator.h"

class Player;
class EnemySpwaner;
class SceneGame;
class UiMsg;
class SceneDev1;

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
	Animator atanimator;
	Animator gunneranimator;

	SpriteGo* ammo;
	UiMsg* uiMsg;


	Types type;
	EnemySpwaner* enemySpawner;
	SceneGame* sceneGame;
	SceneDev1* sceneDev1;

	sf::RenderWindow window;

	sf::Vector2f direction = { 1.f,0.f };
	sf::Vector2f enemyPos = { 0.f,0.f };

	Player* player = nullptr;
	int hp = 100;
	float speed = 100.f;
	float range = 0.f;
	int bullet = 6;

	TextGo* textMsg;
	float timer;
	float attackTimer;
	float interval;
	float removeTimer;
	float moveTimer;
	int missFire;
	int concentration;
	bool ondie = false;
	bool enemyMove = true;
	bool dropAmmo = false;
	bool removeEnemy = false;
	bool disCover = false;
	bool addScore = false;
public:
	Enemy(const std::string& name = "");
	~Enemy() override = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

	SpriteGo* GetAmmo()
	{
		return ammo;
	}

	void TestInstance();
	void PlayerAttack();
	void EnemyDie();

	void Draw(sf::RenderWindow& window)override;
	void Onhit(int d);
	void OnDie(float dt);

	void EnemyHpSet(int h) { hp = h; }
	void SetConcent(int i) { concentration = i; }
	bool GetEnemyDie() { return ondie; }
	void SetMissFire(int i) { missFire = i; }

	int GetEnemyBullet() { return bullet; }

	Types GetType()const { return type; }
};

