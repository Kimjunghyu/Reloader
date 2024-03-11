#include "pch.h"
#include "Gun.h"
#include "Effect.h"
#include "SceneGame.h"
#include "UiMsg.h"
#include "UiHud.h"

Gun::Gun(const std::string& name)
	:SpriteGo(name)
{
}

Gun::~Gun()
{
}

void Gun::TestInstance()
{
	if (bulletCount <= 0)
	{
		animator.Stop();
	}
	if (anistop)
	{
		animator.Stop();
	}
}

void Gun::MissFire()
{
	if (missFire)
	{
		animator.Stop();
	}
}

void Gun::Init()
{
	SpriteGo::Init();
	animator.SetTarget(&sprite);

	effect = new Effect("effect");
	SCENE_MGR.GetCurrentScene()->AddGo(effect);

	uiMsg = new UiMsg("uiMsg");

	uiHud = new UiHud("uiHud");
}

void Gun::Reset()
{
	animator.ClearEvent();

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	effect = dynamic_cast<Effect*>(SCENE_MGR.GetCurrentScene()->FindGo("effect"));
	uiMsg = dynamic_cast<UiMsg*>(SCENE_MGR.GetCurrentScene()->FindGo("uiMsg"));
	uiHud = dynamic_cast<UiHud*>(SCENE_MGR.GetCurrentScene()->FindGo("Hud"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	std::function<void()> funcInstance = std::bind(&Gun::TestInstance, this);
	animator.AddEvent("animations/Gun.csv", 5, funcInstance);

	animator.Play("animations/Gunreturn.csv");
	bulletCount = 6;
}

void Gun::Update(float dt)
{
	animator.Update(dt);
	timer += dt;
	if (timer >= fireinterval)
	{
		isFiring = true;
		timer = 0;
	}
	if (isFiring && InputMgr::GetMouseButtonDown(sf::Mouse::Left) && bulletCount >0 && !missFire)
	{
		animator.Play("animations/Gun.csv");

		if (Utils::RandomRange(0,100) < 95)
		{
			animator.PlayQueue("animations/Gunreturn.csv");
			//sceneGame->AddConcent(10);
		}
		else
		{
			animator.Play("animations/Gunrerr.csv");
			std::function<void()> errgun = std::bind(&Gun::MissFire, this);
			animator.AddEvent("animations/Gunrerr.csv", 5, errgun);
			missFire = true;
		}
		effect->Fire();
		bulletCount -= 1;
		std::cout << bulletCount << std::endl;
		isFiring = false;
		onTarget = true;
	}
	if (missFire)
	{
		uiMsg->GetKeyE(true);
	}
	else if (!missFire)
	{
		uiMsg->GetKeyE(false);
	}
	if (timer == 0)
	{
		onTarget = false;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		bulletCount = 6;
		animator.Resume();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::E))
	{
		missFire = false;
		animator.Resume();

		animator.Play("animations/Gun.csv");
		animator.PlayQueue("animations/Gunreturn.csv");
		uiMsg->GetKeyE(true);
	}
	if (InputMgr::GetKey(sf::Keyboard::E))
	{
		anistop = true;
		isFiring = false;
		uiMsg->GetKeyE(true);
		if (bulletCount > 0&&InputMgr::GetKeyDown(sf::Keyboard::T))
		{
			bulletCount -= 1;
			std::cout << bulletCount << std::endl;
			anistop = false;
			isFiring = true;
			animator.Resume();
			uiMsg->GetKeyE_T(true);
		}
	}
	else
	{
		uiMsg->GetKeyE(false);
		uiMsg->GetKeyE_T(false);
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::E))
	{
		animator.Resume();
		anistop = false;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		uiHud->SetHandMagazine(abs(1 - bulletCount));
		bulletCount = 1;
	}


	SpriteGo::Update(dt);
}

bool Gun::GetEmptyBullet()
{
	if (bulletCount <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
