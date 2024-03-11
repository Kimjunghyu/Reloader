#include "pch.h"
#include "UiMsg.h"
#include "TextGo.h"
#include "Gun.h"

UiMsg::UiMsg(const std::string& name)
	:GameObject(name)
{
}

void UiMsg::Init()
{
	GameObject::Init();
	uiConcentration.Init();
	gun = new Gun("gun");

	sf::Font& font = RES_MGR_FONT.Get("fonts/neodgm.ttf");
	
	for (int i = 0; i <= 9; ++i)
	{
		uiMsg[i].Set(font, "", 30, sf::Color::White);
		uiMsg[i].SetOrigin(Origins::TR);
		uiMsg[i].SetPosition({ 1500.f,-180.f + i * 30 });
	}

	uiConcentration.Set(font, "", 50, sf::Color::Green);
	uiConcentration.SetOrigin(Origins::TL);
	uiConcentration.SetPosition({ -350.f,-130.f });
}

void UiMsg::Reset()
{
	GameObject::Reset();
	uiConcentration.Reset();
	for (int i = 0; i <= 9; ++i)
	{
		uiMsg[i].Reset();
	}
	concent = 100;
}

void UiMsg::Update(float dt)
{
	for (int i = 0; i <= 9; ++i)
	{
		uiMsg[i].Update(dt);
	}
	GameObject::Update(dt);
	uiConcentration.SetString(L"ÁýÁßµµ : " + std::to_wstring(concent));
	uiUpdate();
}

void UiMsg::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i <= 9; ++i)
	{
		uiMsg[i].Draw(window);
	}
	uiConcentration.Draw(window);
	GameObject::Draw(window);
}

void UiMsg::uiUpdate()
{

	uiMsg[0].SetString(L"¹æ¾Æ¼è ´ç±â±â : [LMC]");
	uiMsg[1].SetString(L"Á¤¹Ð Á¶ÁØ : È¦µå [RMC]");
	uiMsg[2].SetString(L"ÅºÃ¢ º§Æ®¿¡¼­ ²¨³»±â : [1] ... [4]");
	uiMsg[3].SetString(L"ÅºÃ¢ ÁÝ±â : [Q]");
	uiMsg[4].SetString(L"Åº³¢ÀÓ Á¦°Å : È¦µå [E]");
	uiMsg[5].SetString(L"ÅºÃ¢ Á¦°Å : [R]");
	uiMsg[6].SetString(L"ÅºÃ¢ °áÇÕ ¹× ¾à½ÇÁ¦°Å : È¦µå[E] + [T]");
	uiMsg[7].SetString(L"Àü¼ú Á¶ÁØ : È¦µå [S]");
	uiMsg[8].SetString(L"ÅºÃ¢ °áÇÕ : [W]");
	uiMsg[9].SetString(L"¾öÆó : È¦µå [C]");

	if (bullet <= 0)
	{
		uiMsg[0].SetFillColor(sf::Color::White);
		uiMsg[5].SetFillColor(sf::Color::Cyan);
	}
	else if (bullet > 0)
	{
		uiMsg[0].SetFillColor(sf::Color::Cyan);
		uiMsg[5].SetFillColor(sf::Color::White);
	}
	if (OnRmc)
	{
		uiMsg[1].SetFillColor(sf::Color::Cyan);
	}
	else if (!OnRmc)
	{
		uiMsg[1].SetFillColor(sf::Color::White);
	}
	if (OnKeyS)
	{
		uiMsg[7].SetFillColor(sf::Color::Cyan);
	}
	else if (!OnKeyS)
	{
		uiMsg[7].SetFillColor(sf::Color::White);
	}
	if (OnKeyE)
	{
		uiMsg[4].SetFillColor(sf::Color::Cyan);
	}
	else if (!OnKeyE)
	{
		uiMsg[4].SetFillColor(sf::Color::White);
	}
	if (OnKeyE_T)
	{
		uiMsg[6].SetFillColor(sf::Color::Cyan);
		OnKeyE = false;
	}
	else if (!OnKeyE_T)
	{
		uiMsg[6].SetFillColor(sf::Color::White);
	}
}
