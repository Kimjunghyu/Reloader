#include "pch.h"
#include "GameOver.h"
#include "pch.h"


GameOver::GameOver(const std::string& name)
	:SpriteGo(name)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
	SpriteGo::Init();
	animator.SetTarget(&sprite);
}

void GameOver::Reset()
{
	animator.ClearEvent();

	animator.Play("animations/gameover.csv");
	SetOrigin(Origins::TL);
	SetScale({ 0.7,0.7 });
	SetPosition({ -300.f,0.f });
}

void GameOver::Update(float dt)
{
	SpriteGo::Update(dt);

	animator.Update(dt);

}
