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
		enemy->textureId = "graphics/gunnerat.png";
		enemy->clipId = "animations/gunnerrun.csv";
		enemy->hp = 100;
		enemy->speed = 100.f;
		enemy->range = 200.f;
		enemy->interval = 2.f;
		enemy->bullet = 6;
		enemy->SetOrigin(Origins::BC);
		break;
	case Enemy::Types::Melee:
		enemy->textureId = "graphics/at.png";
		enemy->clipId = "animations/atrun.csv";
		enemy->hp = 100;
		enemy->speed = 100.f;
		enemy->range = 15.f;
		enemy->interval = 1.f;
		enemy->SetOrigin(Origins::BC);
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
	atanimator.SetTarget(&sprite);
	SetTexture(textureId);
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

	hp = 100;
	atanimator.Play(clipId);
	SetPosition({ 150.f,player->GetPosition().y });

	if (this->type == Types::Distance)
	{
		std::function<void()> funcInstance = std::bind(&Enemy::TestInstance, this);
		atanimator.AddEvent("animations/gunnerrun.csv", 7, funcInstance);

		std::function<void()> funcInstan = std::bind(&Enemy::TestInstance, this);
		atanimator.AddEvent("animations/gunneridle.csv", 7, funcInstan);

		std::function<void()> attackDistance = std::bind(&Enemy::PlayerAttack, this);
		atanimator.AddEvent("animations/atgunner.csv", 3, attackDistance);

		std::function<void()> gunnerdie = std::bind(&Enemy::EnemyDie, this);
		atanimator.AddEvent("animations/gunnerdie.csv", 7, gunnerdie);
	}
	else if (this->type == Types::Melee)
	{
		std::function<void()> funcInstance = std::bind(&Enemy::TestInstance, this);
		atanimator.AddEvent("animations/atrun.csv", 7, funcInstance);

		std::function<void()> funcInstan = std::bind(&Enemy::TestInstance, this);
		atanimator.AddEvent("animations/atidle.csv", 7, funcInstan);

		std::function<void()> attackMelee = std::bind(&Enemy::PlayerAttack, this);
		atanimator.AddEvent("animations/atmille.csv", 3, attackMelee);

		std::function<void()> meleedie = std::bind(&Enemy::EnemyDie, this);
		atanimator.AddEvent("animations/meleedie.csv", 7, meleedie);
	}
}

void Enemy::Update(float dt)
{
	SpriteGo::Update(dt);

	atanimator.Update(dt);

	direction = player->GetPosition() - position;
	Utils::Normalize(direction);
	if (!ondie)
	{
		if (player->GetPosition().x >= GetPosition().x)
		{
			SetFlipX(false);
		}
		else
		{
			SetFlipX(true);
		}
	}

	
	enemyPos = position + direction * speed * dt;
	enemyPos.y = player->GetPosition().y;
	SetPosition(enemyPos);
	sprite.setPosition({ enemyPos.x,enemyPos.y});

	if (this->type == Types::Melee)
	{
		if (!ondie)
		{
			if (sprite.getPosition().x > player->GetPosition().x)
			{
				sprite.setPosition({ enemyPos.x - 10.f,enemyPos.y });
			}
			else
			{
				sprite.setPosition({ enemyPos.x + 10.f,enemyPos.y });
			}
		}
	}
	if (Utils::Distance(player->GetPosition(), GetPosition()) < range)
	{
		speed = 0;
		attackTimer += dt;
		enemyMove = false;
	}
	else if(Utils::Distance(player->GetPosition(), GetPosition()) > range)
	{
		speed = 100.f;
		enemyMove = true;
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
		OnDie(dt);
	}
}

void Enemy::TestInstance()
{

	if (enemyMove)
	{
		atanimator.Stop();
		if (this->type == Types::Distance)
		{
			atanimator.PlayQueue("animations/gunnerrun.csv");
		}
		else if (this->type == Types::Melee)
		{
			atanimator.PlayQueue("animations/atrun.csv");
		}
		atanimator.Resume();
	}
	else if (!enemyMove)
	{
		atanimator.Stop();
		if (this->type == Types::Distance)
		{
			atanimator.PlayQueue("animations/gunneridle.csv");
		}
		else if (this->type == Types::Melee)
		{
			atanimator.PlayQueue("animations/atidle.csv");
		}
		atanimator.Resume();

		if (attackTimer >= interval)
		{
			atanimator.Stop();
			if (this->type == Types::Distance)
			{
				atanimator.PlayQueue("animations/atgunner.csv");
			}
			else if (this->type == Types::Melee)
			{
				atanimator.PlayQueue("animations/atmille.csv");
			}
			atanimator.Resume();
			attackTimer = 0.f;
		}
		else
		{
			return;
		}
	}


}

void Enemy::PlayerAttack()
{
	if (this->type == Types::Distance)
	{
		if (Utils::RandomRange(0, 100) < 50)
		{
			player->Onhit(30);
		}
	}
	else if (this->type == Types::Melee)
	{
		player->Onhit(Utils::RandomRange(1,5) * 10);
	}
}

void Enemy::EnemyDie()
{
	atanimator.Stop();
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

void Enemy::OnDie(float dt)
{
	if (!ondie)
		return;
	if (hp <= 0)
	{
		hp = 0;
		speed = 0;
		if (this->type == Types::Distance)
		{
			atanimator.PlayQueue("animations/gunnerdie.csv");
			removeTimer += dt;
			if (removeTimer >= 4)
			{
				SetActive(false);
				sceneGame->RemoveGo(this);
				sceneGame->AddSpawnCount(1);
				removeTimer = 0.f;
			}
		}
		else if (this->type == Types::Melee)
		{
			atanimator.PlayQueue("animations/meleedie.csv");
			removeTimer += dt;
			if (removeTimer >= 3)
			{
				SetActive(false);
				sceneGame->RemoveGo(this);
				sceneGame->AddSpawnCount(1);
				removeTimer = 0.f;
			}
		}


	}
}
