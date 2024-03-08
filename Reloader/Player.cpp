#include "pch.h"
#include "Player.h"
#include "SceneGame.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::BC);
	animator.SetTarget(&sprite);

	playerArm = new SpriteGo("arm");
	playerArm->SetTexture("graphics/arm1.png");
	playerArm->SetOrigin(Origins::ML);
	playerArm->SetPosition({ 0.f,0.f });
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	animator.Play("animations/playeridle.csv");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f,335.f });
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	animator.Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);


	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	if (animator.GetCurrentClipId() == "animations/playeridle.csv")
	{
		if (direction.x != 0.f)
		{
			animator.PlayQueue("animations/playerrun.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "animations/playerrun.csv")
	{
		if (direction.x == 0.f)
		{
			animator.Play("animations/playeridle.csv");
		}
	}
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}

	sf::Vector2f pos = position + direction * speed * dt;
	SetPosition(pos);

	armPos.x = (sprite.getPosition().x);
	armPos.y = (sprite.getGlobalBounds().top + 20.f);

	look = mouseWorldPos - position;
	Utils::Normalize(look);
	if (!moveArm)
	{
		playerArm->SetRotation(Utils::Angle(look));
	}

	playerArm->SetPosition(armPos);

	if (look.x < 0)
	{
		SetFlipX(true);
	}
	else
	{
		SetFlipX(false);
	}
	if (mouseWorldPos.x < GetPosition().x)
	{
		playerArm->SetFlipY(true);
	}
	else
	{
		playerArm->SetFlipY(false);
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	playerArm->Draw(window);
}

void Player::SetPlayerArmAngle(sf::Vector2f v)
{
	v -= playerArm->GetPosition();
	playerArm->SetRotation(Utils::Angle(v));
}
