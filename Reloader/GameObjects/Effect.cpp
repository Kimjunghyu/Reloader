#include "pch.h"
#include "Effect.h"
#include "Player.h"

Effect::Effect(const std::string& name)
	:SpriteGo(name)
{
}

void Effect::TestInstance()
{
	SetActive(false);
}

void Effect::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::ML);
	animator.SetTarget(&sprite);
}

void Effect::Release()
{
	SpriteGo::Release();
}

void Effect::Reset()
{
	animator.ClearEvent();
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

	std::function<void()> funcInstance = std::bind(&Effect::TestInstance, this);
	animator.AddEvent("animations/FireEffect.csv", 2, funcInstance);

	SetOrigin(Origins::BC);
	//SetScale({ 0.5,0.5 });
	SetPosition({ 0.f,335.f });
}

void Effect::Update(float dt)
{
	SpriteGo::Update(dt);

	animator.Update(dt);


	sf::Vector2f look = SCENE_MGR.GetCurrentScene()->FindGo("cross")->GetPosition();
	look -= GetPosition();
	SetRotation(Utils::Angle(look));

	if (look.x < 0)
	{
		effectPos.x = player->GetGlobalBounds().left - 3.f;
		effectPos.y = player->GetPlayerArm()->GetGlobalBounds().top + player->GetPlayerArm()->GetGlobalBounds().height * 0.5f + 10.f;
		SetPosition(effectPos);
	}
	else if(look.x > 0)
	{
		effectPos.x = player->GetGlobalBounds().left + player->GetGlobalBounds().width + 3.f;
		effectPos.y = player->GetPlayerArm()->GetGlobalBounds().top + player->GetPlayerArm()->GetGlobalBounds().height * 0.5f - 10.f;
		SetPosition(effectPos);
	}


	SetRotation(player->GetPlayerArm()->GetRotation());
}

void Effect::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Effect::Fire()
{
	SetActive(true);
	animator.Play("animations/FireEffect.csv");
}
