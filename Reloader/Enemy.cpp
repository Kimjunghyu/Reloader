#include "pch.h"
#include "Enemy.h"
#include "Player.h"

Enemy* Enemy::Create(Types enemyTypes)
{
	Enemy* enemy = new Enemy("enemy");
	enemy->type = enemyTypes;

	enemy->hp = 100;
	enemy->speed = 100.f;
	return enemy;
}

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

	sf::Vector2f enemyPos = GetPosition();

	direction = player->GetPosition() - position;
	Utils::Normalize(direction);

	if (player->GetPosition().x >= GetPosition().x)
	{
		SetFlipX(false);
	}
	else
	{
		SetFlipX(true);
	}
	sf::Vector2f pos = position + direction * speed * dt;

	SetPosition({pos.x,player->GetPosition().y});

	if (Utils::Distance(player->GetPosition(), GetPosition()) < 200.f)
	{
		speed = 0;
	}
	else
	{
		speed = 100.f;
	}

	sf::Vector2f textPos = GetPosition();
	textMsg->SetPosition({ textPos.x,textPos.y - 100.f });

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
	if (Utils::RandomRange(0.f, 100.f) < concentration)
	{
		hp -= d;
		textMsg->SetString(std::to_string(d));
	}
	else
	{
		hp -= 0;
		textMsg->SetString("Miss");
	}
	textMsg->SetActive(true);
	timer = 0;
	if (hp <= 0)
	{
		hp = 0;
		//SetActive(false);
		//SCENE_MGR.GetCurrentScene()->RemoveGo(this);
		Create(type);
	}

}
