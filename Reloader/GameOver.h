#pragma once
#include "SpriteGo.h"
class GameOver : public SpriteGo
{
protected:
	Animator animator;

public:
	GameOver(const std::string& name = "");
	~GameOver()override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
};
