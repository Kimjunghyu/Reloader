#include "pch.h"
#include "SceneDev1.h"
#include "Gun.h"
#include "TextGo.h"
#include "GameOver.h"


SceneDev1::SceneDev1(SceneIds id) : Scene(id)
{
}

void SceneDev1::Init()
{
	gameOver = new GameOver("gameOver");
	gameOver->SetPosition({ 0.f,0.f });
	gameOver->SetOrigin(Origins::MC);
	AddGo(new GameOver);

	Scene::Init();
	overScene = new SpriteGo("Title");
	overScene->SetTexture("graphics/hardTimeBG.png");
	overScene->SetOrigin(Origins::MC);
	overScene->SetScale({ 1.2f,1.2f });
	overScene->SetPosition({ 0.f,0.f });
	overScene->sortLayer = -1;
	AddGo(overScene);

	uiText = new TextGo("uiText");
	uiText->Set(fontResMgr.Get("fonts/EightBitDragonanqx.ttf"), "", 40, sf::Color::Red);
	uiText->SetString("Game Over");
	uiText->SetPosition({ 0.f,-70.f });
	uiText->SetOrigin(Origins::TC);
	AddGo(uiText);

	uiScore = new TextGo("uiScore");
	uiScore->Set(fontResMgr.Get("fonts/EightBitDragonanqx.ttf"), "", 20, sf::Color::White);
	uiScore->SetString("Press Enter Go To Title");
	uiScore->SetPosition({ 0.f,0.f });
	uiScore->SetOrigin(Origins::TC);
	AddGo(uiScore);

	//uiHiScore = new TextGo("uiHiScore");
	//uiHiScore->Set(fontResMgr.Get("fonts/neodgm.ttf"), "", 20, sf::Color::White);
	//uiHiScore->SetString("Game Over");
	//uiHiScore->SetPosition({ 0.f,30.f });
	//uiHiScore->SetOrigin(Origins::TC);
	//AddGo(uiHiScore);
}

void SceneDev1::Release()
{
	Scene::Release();
}

void SceneDev1::Enter()
{

	Scene::Enter();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::TitleScene);
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
