#include "pch.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(const std::string& name)
	:SpriteGo(name)
{
}

void Enemy::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/test.png");
	SetPosition({ 0.f,0.f });
	SetOrigin(Origins::BC);

	textMsg = new TextGo("textMsg");
	textMsg->Set(RES_MGR_FONT.Get("fonts/Pixel_Digivolve_Cyrillic_font.ttf"), "", 20, sf::Color::Green);
	textMsg->SetPosition({ 0.f, 0.f });
	textMsg->SetOrigin(Origins::MC);

}

void Enemy::Reset()
{
	SpriteGo::Reset();
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	SetPosition({ 150.f,player->GetPosition().y });
	hp = 100;
}

void Enemy::Update(float dt)
{
	SpriteGo::Update(dt);

	SetPosition({ 150.f,player->GetPosition().y });
	sf::Vector2f EnemyPos = GetPosition();
	textMsg->SetPosition({ EnemyPos.x,EnemyPos.y - 100.f });

	timer += dt;
	if (timer >= 3.f)
	{
		textMsg->SetString("");
	}
	if (player->GetPosition().x >= GetPosition().x)
	{
		SetFlipX(false);
	}
	else
	{
		SetFlipX(true);
	}

}

void Enemy::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	textMsg->Draw(window);
}

void Enemy::Onhit(int d)
{
	if (Utils::RandomRange(0.f, 100.f) < concentration)
	{
		hp -= d;
		textMsg->SetString(std::to_string(d));
	}
	else
	{
		hp -= 0;
	}
	textMsg->SetActive(true);
	timer = 0;
	if (hp <= 0)
	{
		hp = 0;
		//SetActive(false);
	}

}
