#include "pch.h"
#include "SceneGame.h"
#include "UiHud.h"
#include "Gun.h"
#include "Player.h"

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
	hud->SetOrigin(Origins::BL);
	hud->SetPosition(centerPos);
	AddGo(hud, Scene::Ui);
	
	test = new SpriteGo("test");
	test->SetTexture("graphics/test.png");
	test->SetPosition({ 0.f,0.f });
	test->SetOrigin(Origins::BC);
	test->SetFlipX(true);
	AddGo(test);

	player = new Player("Player");
	AddGo(player);

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
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	crosshair->SetPosition(ScreenToWorld((sf::Vector2i)InputMgr::GetMousePos()));

	sf::Vector2f worldViewCenter = worldView.getCenter();
	worldViewCenter = Utils::Lerp(worldViewCenter, player->GetPosition(), dt * 3.f);
	worldView.setCenter(worldViewCenter);

	sf::Vector2f gunPos = gun->GetPosition();
	gunPos.x += 175.f;
	gunPos.y += 10.f;
	magazine->SetPosition(gunPos);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		gun->GetisFiring(true);
	}
	bulletMagazine = gun->GetBulletCount();
	if (bulletMagazine <= 0)
	{
		magazine->SetTexture("graphics/emptymagazine.png");
	}
	else
	{
		magazine->SetTexture("graphics/fullmagazine.png");
	}

	test->SetPosition({ 300.f,player->GetPosition().y});

	if (Utils::Distance(test->GetPosition(), crosshair->GetPosition()) <= abs(80.f))
	{
		crosshair->SetPosition({ test->GetPosition().x,test->GetPosition().y - (test->GetGlobalBounds().height*0.7f)});
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

void SceneGame::Fire()
{
}
