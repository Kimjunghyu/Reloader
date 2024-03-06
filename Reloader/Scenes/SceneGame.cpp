#include "pch.h"
#include "SceneGame.h"
#include "UiHud.h"
#include "Gun.h"

SceneGame::SceneGame(SceneIds id)
	: Scene(id)
{

}

void SceneGame::Init()
{
	gun = new Gun("gun");
	gun->SetPosition({ 0.f,0.f });
	gun->SetOrigin(Origins::TC);
	gun->sortLayer = 1;
	AddGo(gun);

	Scene::Init();

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;

	crosshair = new SpriteGo("cross");
	crosshair->SetTexture("graphics/aimTarget.png");
	crosshair->SetScale({ 0.5f,0.5f });
	crosshair->SetPosition({ 0.f,0.f });
	crosshair->SetOrigin(Origins::MC);
	AddGo(crosshair);

	testBg = new SpriteGo("testBg");
	testBg->SetTexture("graphics/testBG.png");
	testBg->SetPosition({0.f,0.f});
	testBg->sortLayer = -1;
	testBg->SetOrigin(Origins::MC);
	AddGo(testBg);

	Magazine = new SpriteGo("magazine");
	Magazine->SetTexture("graphics/magazine.png");
	Magazine->SetOrigin(Origins::TL);
	Magazine->SetPosition({ 1920.f/2 - 500, 1080.f/3 });
	AddGo(Magazine, Scene::Ui);
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
	//sf::Vector2f worldViewCenter = worldView.getCenter();
	//worldViewCenter = Utils::Lerp(worldViewCenter,gunBody->GetPosition(), dt * 2.f);
	//worldView.setCenter(worldViewCenter);

	crosshair->SetPosition(ScreenToWorld((sf::Vector2i)InputMgr::GetMousePos()));

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		gun->GetisFiring(true);
	}
	bulletMagazine = gun->GetBulletCount();
	if (bulletMagazine <= 0)
	{
		Magazine->SetTexture("graphics/emptymagazine.png");
	}
	else
	{
		Magazine->SetTexture("graphics/magazine.png");
	}

}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::Fire()
{
}
