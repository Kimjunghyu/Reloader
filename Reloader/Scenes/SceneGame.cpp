#include "pch.h"
#include "SceneGame.h"
#include "UiHud.h"
#include "Gun.h"
#include "Player.h"
#include "Enemy.h"
#include "Effect.h"
#include "UiMsg.h"

SceneGame::SceneGame(SceneIds id)
	: Scene(id)
{

}

void SceneGame::Init()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;

	gun = new Gun("gun");
	gun->SetPosition({ centerPos.x + 50.f, centerPos.y + 100.f });
	gun->SetOrigin(Origins::BL);
	gun->SetScale({ 2.f,2.f });
	gun->sortLayer = 1;
	AddGo(gun, Scene::Ui);

	crosshair = new SpriteGo("cross");
	crosshair->SetTexture("graphics/MouseTarget.png");
	crosshair->SetPosition({ 0.f,0.f });
	crosshair->SetOrigin(Origins::MC);
	crosshair->sortLayer = 1;
	AddGo(crosshair);

	testBg = new SpriteGo("testBg");
	testBg->SetTexture("graphics/stage3_bg_render_slow.png");
	testBg->SetPosition({0.f,0.f});
	testBg->sortLayer = -1;
	testBg->SetOrigin(Origins::MC);
	AddGo(testBg);

	magazine = new SpriteGo("magazine");
	magazine->SetTexture("graphics/fullmagazine.png");
	magazine->SetOrigin(Origins::TC);
	magazine->SetPosition(centerPos);
	magazine->SetScale({ 2.f,2.f });
	magazine->sortLayer = 0;
	AddGo(magazine, Scene::Ui);

	hud = new UiHud("Hud");
//	hud->SetOrigin(Origins::BL);
	hud->SetPosition(centerPos);
	AddGo(hud, Scene::Ui);

	enemy = new Enemy("enemy");
	AddGo(enemy);

	effect = new Effect("effect");
	AddGo(effect);

	player = new Player("Player");
	AddGo(player);

	uiMsg = new UiMsg("uiMsg");
	uiMsg->SetOrigin(Origins::TR);
	AddGo(uiMsg,Scene::Ui);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
}

void SceneGame::Exit()
{
	Scene::Exit();
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
}

void SceneGame::Reset()
{
	conCent = 100.f;
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	crosshair->SetPosition(ScreenToWorld((sf::Vector2i)InputMgr::GetMousePos()));

	sf::Vector2f worldViewCenter = worldView.getCenter();

	worldViewCenter = Utils::Lerp(worldViewCenter, { player->GetPosition().x,player->GetPosition().y - 75.f}, dt * 3.f);
	worldView.setCenter(worldViewCenter);

	sf::Vector2f gunPos = gun->GetPosition();
	gunPos.x += 175.f;
	gunPos.y += 10.f;
	magazine->SetPosition(gunPos);

	bulletMagazine = gun->GetBulletCount();
	uiMsg->GetBullet(bulletMagazine);

	if (bulletMagazine <= 0)
	{
		magazine->SetTexture("graphics/emptymagazine.png");
	}
	else
	{
		magazine->SetTexture("graphics/fullmagazine.png");
	}

	fireTimer += dt;
	if (Utils::Distance(enemy->GetPosition(), crosshair->GetPosition()) <= abs(80.f))
	{
		crosshair->SetPosition({ enemy->GetPosition().x,enemy->GetPosition().y - (enemy->GetGlobalBounds().height*0.7f)});
		crosshair->SetTexture("graphics/aimTarget1.png");
		player->SetMoveArm(true);
		player->SetPlayerArmAngle(crosshair->GetPosition());

		if (InputMgr::GetMouseButton(sf::Mouse::Right))
		{
			crosshair->SetScale({ 1.5f,1.5f });
			crosshair->SetPosition({ enemy->GetPosition().x,enemy->GetPosition().y - (enemy->GetGlobalBounds().height - 5.f) });
			player->SetPlayerArmAngle(crosshair->GetPosition());
			EnemyHit(100);
			uiMsg->GetRmc(true);
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)&&bulletMagazine != 0 && fireTimer >= 1)
			{
				conCent -= 10;
				if (conCent <= 0)
				{
					conCent = 0;
				}
				uiMsg->UiConcent(conCent);
				enemy->SetConcent(conCent);
				fireTimer = 0;
			}
		}
		else if (InputMgr::GetKey(sf::Keyboard::S))
		{
			crosshair->SetPosition({ enemy->GetPosition().x,enemy->GetPosition().y - 5.f });
			player->SetPlayerArmAngle(crosshair->GetPosition());
			EnemyHit(40);
			uiMsg->GetKeyS(true);
		}
		else
		{
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)&& bulletMagazine != 0 && fireTimer >= 0)
			{
				conCent += 10;
				if (conCent >= 100)
				{
					conCent = 100;
				}
				uiMsg->UiConcent(conCent);
				enemy->SetConcent(conCent);
				fireTimer = 0;
			}
			EnemyHit(50);
			uiMsg->GetRmc(false);
			uiMsg->GetKeyS(false);
		}
	}
	else
	{
		player->SetMoveArm(false);
		crosshair->SetTexture("graphics/MouseTarget.png");
	}

	if (player->GetPosition().y == 335.f)
	{
		if (player->GetPosition().x >= 700.f)
		{
			player->SetPosition({ player->GetPosition().x - 75.f, -70.f });
		}
		else if (player->GetPosition().x <= -400.f)
		{
			player->SetPosition({ -800.f,-70.f });
		}
	}

	if (player->GetPosition().y == -70.f)
	{
		if (player->GetPosition().x >= 700.f)
		{
			player->SetPosition({ player->GetPosition().x - 75.f, 335.f });
		}
		else if (player->GetPosition().x <= -850.f)
		{
			player->SetPosition({ -350.f, 335.f });
		}
	}
	timer += dt;
	if (timer >= 1)
	{
		if (conCent < 100)
		{
			conCent += 1;
			uiMsg->UiConcent(conCent);
		}
		else if (conCent >= 100)
		{
			conCent = 100;
			uiMsg->UiConcent(conCent);
		}
		timer = 0;
	}
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	hud->Draw(window);
}

void SceneGame::EnemyHit(int d)
{
	if (gun->GetOnTarget() != false && InputMgr::GetMouseButtonDown(sf::Mouse::Left) && bulletMagazine > 0)
	{
		enemy->Onhit(d);
	}
}

void SceneGame::AddConcent(int i)
{
	conCent += i;
	if (conCent >= 100)
	{
		conCent = 100;
	}
	uiMsg->UiConcent(conCent);
	enemy->SetConcent(conCent);
}

