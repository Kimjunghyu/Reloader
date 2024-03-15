#include "pch.h"
#include "SceneGame.h"
#include "UiHud.h"
#include "Gun.h"
#include "Player.h"
#include "Enemy.h"
#include "Effect.h"
#include "UiMsg.h"
#include "EnemySpwaner.h"

SceneGame::SceneGame(SceneIds id)
	: Scene(id)
{

}

void SceneGame::Init()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;

	enemySpawners.push_back(new EnemySpwaner);
	for (auto e : enemySpawners)
	{
		e->SetPosition({ 0.f,0.f });
		AddGo(e,Scene::World);
	}

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
	testBg->SetTexture("graphics/background2.png");
	testBg->SetPosition({0.f,0.f});
	testBg->sortLayer = -1;
	testBg->SetOrigin(Origins::MC);
	AddGo(testBg);

	magazine = new SpriteGo("magazine");
	magazine->SetTexture("graphics/fullmagazine.png");
	magazine->SetOrigin(Origins::TC);
	gunPos = gun->GetPosition();
	gunPos.x += 175.f;
	gunPos.y += 10.f;
	magazine->SetPosition(gunPos);
	magazine->SetScale({ 2.f,2.f });
	magazine->sortLayer = 0;
	AddGo(magazine, Scene::Ui);

	hud = new UiHud("Hud");
	hud->SetPosition(centerPos);
	AddGo(hud, Scene::Ui);

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
	enemySpawners[0]->SetActive(false);
	spawnCount = 3;
}

void SceneGame::Exit()
{
	Scene::Exit();
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
}

void SceneGame::Reset()
{
	conCent = 100.f;

	auto& list = GetEnemyList();
	for (auto Go : list)
	{
		if (!Go->GetActive())
			continue;
		Enemy* enemy = dynamic_cast<Enemy*>(Go);
		if (enemy != nullptr)
		{
			RemoveGo(enemy);
		}
	}
}

void SceneGame::Update(float dt)
{
	FindGoAll("enemy", enemyList, Layers::World);

	Scene::Update(dt);
	crosshair->SetPosition(ScreenToWorld((sf::Vector2i)InputMgr::GetMousePos()));
	sf::Vector2f worldViewCenter = worldView.getCenter();

	player->SetMoveArm(false);

	worldViewCenter = Utils::Lerp(worldViewCenter, { player->GetPosition().x,player->GetPosition().y - 75.f}, dt * 3.f);
	worldView.setCenter(worldViewCenter);

	bulletMagazine = gun->GetBulletCount();
	uiMsg->GetBullet(bulletMagazine);
	if (bulletMagazine <= 0 || !onMagazine)
	{
		magazine->SetTexture("graphics/emptymagazine.png");
	}
	else if (bulletMagazine > 0 || onMagazine)
	{
		magazine->SetTexture("graphics/fullmagazine.png");
	}
	if (enemyList.size() < 3)
	{
		spawnTimer += dt;
		if (spawnTimer >= 8.f)
		{
			enemySpawners[0]->Spawn(spawnCount);
			spawnCount = 0;
			spawnTimer = 0.f;
		}

	}

	fireTimer += dt;
	auto& list = GetEnemyList();
	for (auto& Go : list)
	{
		if (!Go->GetActive())
			continue;
		Enemy* enemy = dynamic_cast<Enemy*>(Go);
		if (enemy != nullptr)
		{
			if (!enemy->GetEnemyDie() && Utils::Distance(enemy->GetPosition(), crosshair->GetPosition()) <= abs(80.f))
			{
				onTarget = true;

				crosshair->SetPosition({ enemy->GetPosition().x,enemy->GetPosition().y - (enemy->GetGlobalBounds().height * 0.7f) });
				crosshair->SetTexture("graphics/aimTarget1.png");
				player->SetMoveArm(true);
				player->SetPlayerArmAngle(crosshair->GetPosition());

				if (InputMgr::GetMouseButton(sf::Mouse::Right))
				{
					crosshair->SetScale({ 1.5f,1.5f });
					crosshair->SetPosition({ enemy->GetPosition().x,enemy->GetPosition().y - (enemy->GetGlobalBounds().height - 5.f) });
					player->SetPlayerArmAngle(crosshair->GetPosition());
					if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && bulletMagazine > 0 && fireTimer >= 0.5f && !errGun)
					{
						if (Utils::RandomRange(0, 100) < conCent)
						{
							enemy->Onhit(100);
							fireTimer = 0;
						}
						else
						{
							enemy->Onhit(0);
							fireTimer = 0;
						}
						conCent -= 10;
						if (conCent <= 0)
						{
							conCent = 0;
						}
						uiMsg->UiConcent(conCent);
						fireTimer = 0;
						break;
					}
					uiMsg->GetRmc(true);
					uiMsg->GetKeyS(false);
				}
				else if (InputMgr::GetKey(sf::Keyboard::S))
				{
					crosshair->SetPosition({ enemy->GetPosition().x,enemy->GetPosition().y - 5.f });
					player->SetPlayerArmAngle(crosshair->GetPosition());
					if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && bulletMagazine > 0 && fireTimer >= 0.5f && !errGun)
					{
						if (Utils::RandomRange(0, 100) < conCent)
						{
							enemy->Onhit(40);
							fireTimer = 0;
						}
						else
						{
							enemy->Onhit(0);
							fireTimer = 0;
						}
						break;
					}
					uiMsg->GetKeyS(true);
					uiMsg->GetRmc(false);
				}
				else
				{
					if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && bulletMagazine > 0 && fireTimer >= 0.5f && !errGun)
					{
						if (Utils::RandomRange(0, 100) < conCent)
						{
							enemy->Onhit(50);
							fireTimer = 0;
						}
						else
						{
							enemy->Onhit(0);
							fireTimer = 0;
						}
						conCent += 10;
						if (conCent >= 100)
						{
							conCent = 100;
						}
						uiMsg->UiConcent(conCent);
						break;
					}
					uiMsg->GetRmc(false);
					uiMsg->GetKeyS(false);
				}
				break;
			}
			else
			{
				uiMsg->GetRmc(false);
				onTarget = false;
				player->SetMoveArm(false);
				crosshair->SetTexture("graphics/MouseTarget.png");
			}
		}
	}

	for (auto& Go : list)
	{
		if (!Go->GetActive())
			continue;
		Enemy* enemy = dynamic_cast<Enemy*>(Go);
		if (enemy != nullptr)
		{
			if (!enemyDie)
			{
				if (Utils::Distance(player->GetPosition(), enemy->GetPosition()) < 250.f)
				{
					uiMsg->GetDisCover(true);
				}
				else
				{
					uiMsg->GetDisCover(false);
				}
				if (playerSit)
				{
					enemy->SetMissFire(30);
				}
				else
				{
					enemy->SetMissFire(50);
				}
				break;
			}
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

void SceneGame::AddConcent(int i)
{
	conCent += i;
	if (conCent >= 100)
	{
		conCent = 100;
	}
	uiMsg->UiConcent(conCent);
}
