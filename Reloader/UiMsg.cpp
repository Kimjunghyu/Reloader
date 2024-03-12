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
	discovered.Init();
	uiHp.Init();
	gun = new Gun("gun");

	sf::Font& font = RES_MGR_FONT.Get("fonts/neodgm.ttf");
	
	for (int i = 0; i <= 10; ++i)
	{
		uiMsg[i].Set(font, "", 30, sf::Color::White);
		uiMsg[i].SetOrigin(Origins::TR);
		uiMsg[i].SetPosition({ 1500.f,-130.f + i * 30 });
	}

	uiConcentration.Set(font, "", 50, sf::Color::Green);
	uiConcentration.SetOrigin(Origins::TL);
	uiConcentration.SetPosition({ -350.f,-130.f });

	discovered.Set(font, "", 40, sf::Color::Yellow);
	discovered.SetOrigin(Origins::TR);
	discovered.SetPosition({ 1500.f,-180.f });

	uiHp.Set(font, "", 50, sf::Color::White);
	uiHp.SetOrigin(Origins::TL);
	uiHp.SetPosition({ -350.f,-200.f });
}

void UiMsg::Reset()
{
	GameObject::Reset();
	uiConcentration.Reset();
	uiHp.Reset();
	for (int i = 0; i <= 9; ++i)
	{
		uiMsg[i].Reset();
	}
	concent = 100;
	hp = 100;
}

void UiMsg::Update(float dt)
{
	for (int i = 0; i <= 10; ++i)
	{
		uiMsg[i].Update(dt);
	}
	GameObject::Update(dt);

	uiUpdate();
}

void UiMsg::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i <= 10; ++i)
	{
		uiMsg[i].Draw(window);
	}
	uiConcentration.Draw(window);
	discovered.Draw(window);
	uiHp.Draw(window);
	GameObject::Draw(window);
}

void UiMsg::uiUpdate()
{

	uiMsg[0].SetString(L"��Ƽ� ���� : [LMC]");
	uiMsg[1].SetString(L"���� ���� : Ȧ�� [RMC]");
	uiMsg[2].SetString(L"źâ��Ʈ Ȯ�� : Ȧ�� [1] ... [4]");
	uiMsg[3].SetString(L"źâ ��Ʈ���� ������ : Ȧ�� [1] ... [4] + [SPACE]");
	uiMsg[4].SetString(L"źâ �ݱ� : [Q]");
	uiMsg[5].SetString(L"ź���� ���� : Ȧ�� [E]");
	uiMsg[6].SetString(L"źâ ���� : [R]");
	uiMsg[7].SetString(L"źâ ���� �� ������� : Ȧ��[E] + [T]");
	uiMsg[8].SetString(L"���� ���� : Ȧ�� [S]");
	uiMsg[9].SetString(L"źâ ���� : [W]");
	uiMsg[10].SetString(L"��ũ���� : Ȧ�� [C]");

	uiConcentration.SetString(L"���ߵ� : " + std::to_wstring(concent) + L"%");
	discovered.SetString(L"[�߰���]");
	uiHp.SetString(L"���� : " + std::to_wstring(hp) + L"%");

	if (emptyGun)
	{
		uiMsg[0].SetFillColor(sf::Color::White);
		if (handBullet)
		{
			uiMsg[8].SetFillColor(sf::Color::Cyan);
		}
		else if (!handBullet)
		{
			uiMsg[8].SetFillColor(sf::Color::White);
		}
	}
	else if (!emptyGun)
	{
		uiMsg[0].SetFillColor(sf::Color::Cyan);
		uiMsg[8].SetFillColor(sf::Color::White);
		uiMsg[8].SetFillColor(sf::Color::White);
	}
	if (!handBullet)
	{
		uiMsg[3].SetFillColor(sf::Color::Cyan);
	}
	else if (handBullet)
	{
		uiMsg[3].SetFillColor(sf::Color::White);
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
	if (DisCover)
	{
		discovered.SetFillColor(sf::Color::Red);
	}
	else if (!DisCover)
	{
		discovered.SetFillColor(sf::Color::Yellow);
	}
}
