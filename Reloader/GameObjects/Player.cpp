#include "pch.h"
#include "Player.h"
#include "SceneGame.h"
#include "UiMsg.h"
#include "Enemy.h"
#include "UiHud.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{
}

void Player::TestInstance()
{
	if (playerSit)
	{
		animator.Stop();
		playerMove = false;
	}
	else if (!playerSit)
	{
		animator.Play("animations/playerrun.csv");
		animator.Resume();
	}
	if (noDamage)
	{
		noDamage = false;
	}
	else
	{
		return;
	}
	if (addMagazine)
	{

	}
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
	uiMsg = dynamic_cast<UiMsg*>(SCENE_MGR.GetCurrentScene()->FindGo("uiMsg"));
	uiHud = dynamic_cast<UiHud*>(SCENE_MGR.GetCurrentScene()->FindGo("uiHud"));

	animator.Play("animations/playeridle.csv");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f,250.f });
	std::function<void()> funcInstance = std::bind(&Player::TestInstance, this);
	animator.AddEvent("animations/playersit.csv", 4, funcInstance);

	std::function<void()> playerhit = std::bind(&Player::TestInstance, this);
	animator.AddEvent("animations/playerhit.csv", 7, playerhit);
	hp = maxHp;
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	uiMsg->GetHp(hp);
	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	if (playerMove)
	{
		direction.x = InputMgr::GetAxis(Axis::Horizontal);
	}
	else if (!playerMove)
	{
		direction.x = 0.f;
	}


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

	if (InputMgr::GetKeyDown(sf::Keyboard::C) || InputMgr::GetKeyDown(sf::Keyboard::Q))
	{
		animator.Play("animations/playersit.csv");
		SOUND_MGR.PlaySfx("sound/footstep5.wav");
		if (InputMgr::GetKey(sf::Keyboard::C))
		{
			playerSit = true;
			uiMsg->PlayerSit(true);
		}
		if (InputMgr::GetKey(sf::Keyboard::Q))
		{
			playerSit = true;
			if (addMagazine)
			{
				uiMsg->AddMagazine(true);
			}
		}
	}
	else if (InputMgr::GetKeyUp(sf::Keyboard::C) || InputMgr::GetKeyUp(sf::Keyboard::Q))
	{
		playerSit = false;
		animator.Resume();
		playerMove = true;
		uiMsg->PlayerSit(false);
		uiMsg->AddMagazine(false);
	}

	if (!playerSit)
	{
		armPos.y = (sprite.getGlobalBounds().top + 30.f);
		sceneGame->PlayerSit(false);
	}
	else
	{
		armPos.y = (sprite.getGlobalBounds().top + 35.f);
		sceneGame->PlayerSit(true);
	}
	armPos.x = (sprite.getPosition().x);

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
	timer += dt;

	if (timer >= 5.f)
	{
		hp += 10;
		if (hp >= maxHp)
		{
			hp = maxHp;
		}
		timer = 0;
	}

	if (noDamage)
	{
		timer = 0;
	}

	if (hp > 0)
	{
		isAlive = true;
		SetActive(true);
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

void Player::Onhit(int i)
{
	if (!isAlive)
		return;
	SOUND_MGR.PlaySfx("sound/meleeHit.wav");
	if (!noDamage)
	{
		animator.PlayQueue("animations/playerhit.csv");
		hp -= i;
		noDamage = true;
	}
	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Player::OnDie()
{
	if (!isAlive)
		return;

	isAlive = false;
	SetActive(false);
}
