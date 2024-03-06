#pragma once
#include "Scene.h"

class Player;
class UiHud;
class SpriteGo;
class Gun;

class SceneGame : public Scene
{
protected:
	SpriteGo* testBg;
	UiHud* hud;
	SpriteGo* crosshair;
	Gun* gun;
	SpriteGo* magazine;
	Player* player;

	float speed = 100.f;
	sf::Vector2f firedirection = { 0.f,0.f };
	sf::Vector2f direction = { 1.f,0.f };
	float timer = 0.f;
	float delay = 1.0;

	int bulletMagazine;
	bool isFiring = false;
public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

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

	void Fire();
};

