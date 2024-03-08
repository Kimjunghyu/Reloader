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
	SetFlipX(true);

	textMsg = new TextGo("textMsg");
	textMsg->Set(RES_MGR_FONT.Get("fonts/Pixel_Digivolve_Cyrillic_font.ttf"), "", 20, sf::Color::Green);
	textMsg->SetPosition({ 0.f, 0.f });
	textMsg->SetOrigin(Origins::MC);

}

void Enemy::Reset()
{
	SpriteGo::Reset();
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	SetPosition({ 200.f,player->GetPosition().y });
	hp = 100;
}

void Enemy::Update(float dt)
{
	SpriteGo::Update(dt);

	SetPosition({ 200.f,player->GetPosition().y });
	sf::Vector2f EnemyPos = GetPosition();
	textMsg->SetPosition({ EnemyPos.x,EnemyPos.y - 100.f });

	timer += dt;
	if (timer >= 3.f)
	{
		textMsg->SetString("");
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	textMsg->Draw(window);
}

void Enemy::Onhit(int d)
{
	hp -= d;
	textMsg->SetActive(true);
	timer = 0;
	if (hp <= 0)
	{
		hp = 0;
		//SetActive(false);
	}
	textMsg->SetString(std::to_string(d));
}
