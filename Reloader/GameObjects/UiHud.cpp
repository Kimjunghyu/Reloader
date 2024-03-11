#include "pch.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetResoultion(const sf::Vector2f resoution)
{
}

void UiHud::Update(float dt)
{
	GameObject::Update(dt);

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;

	sf::Vector2f frame1Pos = frame1.GetPosition();
	sf::Vector2f frame2Pos = frame2.GetPosition();
	sf::Vector2f frame3Pos = frame3.GetPosition();
	sf::Vector2f frame4Pos = frame4.GetPosition();

	if (InputMgr::GetKey(sf::Keyboard::Num1))
	{
		frame1Pos.y -=speed * dt;
		frame1.SetPosition(frame1Pos);
		if (frame1Pos.y <= 500.f)
		{
			frame1Pos.y = 500.f;
			frame1.SetPosition(frame1Pos);
		}
	}
	else
	{
		frame1Pos.y += speed * dt;
		frame1.SetPosition(frame1Pos);
		if (frame1Pos.y >= 800.f)
		{
			frame1Pos.y = 800.f;
			frame1.SetPosition(frame1Pos);
		}
	}
	if (InputMgr::GetKey(sf::Keyboard::Num2))
	{
		frame2Pos.y -= speed * dt;
		frame2.SetPosition(frame2Pos);
		if (frame2Pos.y <= 500.f)
		{
			frame2Pos.y = 500.f;
			frame2.SetPosition(frame2Pos);
		}
	}
	else
	{
		frame2Pos.y += speed * dt;
		frame2.SetPosition(frame2Pos);
		if (frame2Pos.y >= 800.f)
		{
			frame2Pos.y = 800.f;
			frame2.SetPosition(frame2Pos);
		}
	}
	if (InputMgr::GetKey(sf::Keyboard::Num3))
	{
		frame3Pos.y -= speed * dt;
		frame3.SetPosition(frame3Pos);
		if (frame3Pos.y <= 500.f)
		{
			frame3Pos.y = 500.f;
			frame3.SetPosition(frame3Pos);
		}
	}
	else
	{
		frame3Pos.y += speed * dt;
		frame3.SetPosition(frame3Pos);
		if (frame3Pos.y >= 800.f)
		{
			frame3Pos.y = 800.f;
			frame3.SetPosition(frame3Pos);
		}
	}
	if (InputMgr::GetKey(sf::Keyboard::Num4))
	{
		frame4Pos.y -= speed * dt;
		frame4.SetPosition(frame4Pos);
		if (frame4Pos.y <= 500.f)
		{
			frame4Pos.y = 500.f;
			frame4.SetPosition(frame4Pos);
		}
	}
	else
	{
		frame4Pos.y += speed * dt;
		frame4.SetPosition(frame4Pos);
		if (frame4Pos.y >= 800.f)
		{
			frame4Pos.y = 800.f;
			frame4.SetPosition(frame4Pos);
		}
	}
	magazinePos.x = (handFrame.GetGlobalBounds().left + handFrame.GetGlobalBounds().width);
	magazinePos.y = (handFrame.GetGlobalBounds().top + handFrame.GetGlobalBounds().height);
	handMagazine.SetPosition(magazinePos);

	if (handBullet > 0)
	{
		handMagazine.SetTexture("graphics/fullmagazine.png");
	}
	else if (handBullet <= 0)
	{
		handMagazine.SetTexture("graphics/emptymagazine.png");
	}

}

void UiHud::Init()
{
	frame1.Init();
	frame2.Init();
	frame3.Init();
	frame4.Init();
	handFrame.Init();
	handMagazine.Init();

	frame1.SetTexture("graphics/inventoryFrame1.png");
	frame2.SetTexture("graphics/inventoryFrame2.png");
	frame3.SetTexture("graphics/inventoryFrame3.png");
	frame4.SetTexture("graphics/inventoryFrame4.png");
	handFrame.SetTexture("graphics/inventoryFrame.png");
	handMagazine.SetTexture("graphics/emptymagazine.png");

	frame1.SetScale({ 2.f,2.f });
	frame2.SetScale({ 2.f,2.f });
	frame3.SetScale({ 2.f,2.f });
	frame4.SetScale({ 2.f,2.f });
	handFrame.SetScale({ 2.f,2.f });
	handMagazine.SetScale({ 2.f,2.f });

	frame1.SetOrigin(Origins::TL);
	frame2.SetOrigin(Origins::TL);
	frame3.SetOrigin(Origins::TL);
	frame4.SetOrigin(Origins::TL);
	handFrame.SetOrigin(Origins::TL);
	handMagazine.SetOrigin(Origins::BR);

	frame1.SetPosition({ -300.f,800.f });
	frame2.SetPosition({ -100.f,800.f});
	frame3.SetPosition({ 100.f,800.f });
	frame4.SetPosition({ 300.f,800.f });
	handFrame.SetPosition({ 850.f,600.f });
	handMagazine.SetPosition({ 0.f,0.f });

	speed = 1500.f;

	gun = new Gun("gun");
}

void UiHud::Reset()
{
	GameObject::Reset();
	frame1.Reset();
	frame2.Reset();
	frame3.Reset();
	frame4.Reset();
}

void UiHud::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);

	frame1.Draw(window);
	frame2.Draw(window);
	frame3.Draw(window);
	frame4.Draw(window);
	handFrame.Draw(window);
	handMagazine.Draw(window);
}

void UiHud::SetHandMagazine(int i)
{
	handBullet = i;
}
