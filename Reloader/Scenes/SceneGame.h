#pragma once
#include "Scene.h"

class Player;
class UiHud;
class SpriteGo;
class Gun;
class Enemy;
class Effect;
class UiMsg;
class Spawner;

class SceneGame : public Scene
{
protected:
	SpriteGo* testBg;
	UiHud* hud;
	SpriteGo* crosshair;
	Gun* gun;
	SpriteGo* magazine;
	Player* player;
	Enemy* enemy = nullptr;
	Effect* effect;
	UiMsg* uiMsg;

	std::vector<Spawner*> enemySpawners;
	std::list<GameObject*> enemyList;

	float speed = 100.f;
	sf::Vector2f firedirection = { 0.f,0.f };
	sf::Vector2f direction = { 1.f,0.f };
	sf::Vector2f gunPos = { 0.f,0.f };

	float timer = 0.f;
	float fireTimer = 0.f;
	float delay = 1.0;
	int conCent = 100.f;
	float magazineSpeed = 10.f;
	int spawnCount = 0;

	int bulletMagazine;
	bool isFiring = true;
	bool onMagazine = true;
	bool onTarget = false;
	bool onDie = false;
	bool errGun = false;

	float spawnTimer = 3.f;
public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	const std::list<GameObject*>& GetEnemyList() const { return enemyList; }

	UiHud* GetHud() const
	{
		return hud;
	}

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;
	void Reset();

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void AddConcent(int i);

	void SetMagazine(bool b) { onMagazine = b; }
	void AddSpawnCount(int i) { spawnCount += i; }
	void SetErrGun(bool b) { errGun = b; }
	void SetFiring(bool b) { isFiring = b; }
};

