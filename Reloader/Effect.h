#pragma once
#include "SpriteGo.h"

class SceneGame;
class Player;

class Effect : public SpriteGo
{
protected:
	Animator animator;
	Player* player = nullptr;
	SceneGame* sceneGame = nullptr;
public:
	Effect(const std::string& name = "");
	~Effect() override = default;

	void TestInstance();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire();
};

