#include "pch.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemySpwaner.h"
#include "SceneGame.h"

Enemy* Enemy::Create(Types enemyTypes)
{
	Enemy* enemy = new Enemy("enemy");
	enemy->type = enemyTypes;

	switch (enemyTypes)
	{
	case Enemy::Types::Distance:
		enemy->textureId = "graphics/test.png";
		enemy->hp = 100;
		enemy->speed = 100.f;
		enemy->range = 200.f;
		break;
	case Enemy::Types::Melee:
		enemy->textureId = "graphics/test2.png";
		enemy->hp = 100;
		enemy->speed = 110.f;
		enemy->range = 10.f;
		break;
	}
	return enemy;
}

Enemy::Enemy(const std::string& name)
	:SpriteGo(name)
{
}

void Enemy::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
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
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	enemySpawner = dynamic_cast<EnemySpwaner*>(SCENE_MGR.GetCurrentScene()->FindGo("enemy"));
	SetPosition({ 150.f,player->GetPosition().y });
	hp = 100;
}

void Enemy::Update(float dt)
{
	SpriteGo::Update(dt);

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

	if (Utils::Distance(player->GetPosition(), GetPosition()) < range)
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
	if (hp > 0)
	{
		ondie = false;
	}
	else if (hp <= 0)
	{
		ondie = true;
		OnDie();
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
	textMsg->SetString(std::to_string(d));
	textMsg->SetActive(true);
	timer = 0;
}

void Enemy::OnDie()
{
	if (!ondie)
		return;

	if (hp <= 0)
	{
		hp = 0;
		SetActive(false);
		sceneGame->RemoveGo(this);
		sceneGame->AddSpawnCount(1);
	}
}
