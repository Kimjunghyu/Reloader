#include "pch.h"
#include "TitleScene.h"
#include "SpriteGo.h"
#include "TextGo.h"


TitleScene::TitleScene(SceneIds id)
	:Scene(id)
{
}

void TitleScene::Init()
{	
	Scene::Init();
	titleTexture = new SpriteGo("Title");
	titleTexture->SetTexture("graphics/hardTimeBG.png");
	titleTexture->SetScale({ 4.f,4.f });
	titleTexture->sortLayer = -1;
	AddGo(titleTexture);

	title = new SpriteGo("titlename");
	title->SetTexture("graphics/reloader_TS_logo Fit.png");
	title->sortLayer = 0;
	title->SetOrigin(Origins::MC);
	title->SetPosition({ 1920.f / 2,300.f });
	AddGo(title);

	uiText = new TextGo("uiText");
	uiText->Set(fontResMgr.Get("fonts/EightBitDragonanqx.ttf"), "", 75, sf::Color::White);
	uiText->SetString("Press Enter To Start!");
	uiText->SetPosition({ 1920.f / 2, 1080.f - 200 });
	uiText->SetOrigin(Origins::MC);
	AddGo(uiText);
}

void TitleScene::Release()
{
	Scene::Release();
}

void TitleScene::Enter()
{
	Scene::Enter();

	SOUND_MGR.PlayBgm("sound/SilentBGM.wav", true);
}

void TitleScene::Update(float dt)
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ centerPos });

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneGame);
	}
}

void TitleScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
