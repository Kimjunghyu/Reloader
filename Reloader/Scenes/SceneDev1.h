#pragma once
#include "Animator.h"

class SpriteGo;
class TextGo;
class GameOver;

class SceneDev1 : public Scene
{
protected:
	GameOver* gameOver;

	SpriteGo* overScene = nullptr;
	TextGo* uiText = nullptr;
	TextGo* uiScore;
	TextGo* uiHiScore;

	int score;
	int hiScore;
	sf::RenderWindow window;

public:
	SceneDev1(SceneIds id);
	~SceneDev1()override = default;

	void Init() override;
	void Release() override;

	void Enter() override;

	void Update(float dt) override;

	void SetScore(int i);
	void SetHiScore(int i);

	void Draw(sf::RenderWindow& window) override;
};

