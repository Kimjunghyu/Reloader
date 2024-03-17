#include "pch.h"
#include "UiHud.h"
#include "UiMsg.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::Update(float dt)
{
	GameObject::Update(dt);

	sf::Vector2f frame1Pos = frame[0].GetPosition();
	sf::Vector2f frame2Pos = frame[1].GetPosition();
	sf::Vector2f frame3Pos = frame[2].GetPosition();
	sf::Vector2f frame4Pos = frame[3].GetPosition();

	if (InputMgr::GetKey(sf::Keyboard::Num1))
	{
		frame1Pos.y -=speed * dt;
		frame[0].SetPosition(frame1Pos);
		if (frame1Pos.y <= 500.f)
		{
			frame1Pos.y = 500.f;
			frame[0].SetPosition(frame1Pos);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Space) && handBullet == 0)
		{
			handBullet = frameBullet[0];
			frameBullet[0] = 0;
		}
		else if(InputMgr::GetKeyDown(sf::Keyboard::Space) && handBullet > 0)
		{
			frameBullet[0] = handBullet;
			handBullet = 0;
		}
	}
	else
	{
		frame1Pos.y += speed * dt;
		frame[0].SetPosition(frame1Pos);
		if (frame1Pos.y >= 800.f)
		{
			frame1Pos.y = 800.f;
			frame[0].SetPosition(frame1Pos);
		}
	}
	if (InputMgr::GetKey(sf::Keyboard::Num2))
	{
		frame2Pos.y -= speed * dt;
		frame[1].SetPosition(frame2Pos);
		if (frame2Pos.y <= 500.f)
		{
			frame2Pos.y = 500.f;
			frame[1].SetPosition(frame2Pos);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Space) && handBullet == 0)
		{
			handBullet = frameBullet[1];
			frameBullet[1] = 0;
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Space) && handBullet > 0)
		{
			frameBullet[1] = handBullet;
			handBullet = 0;
		}
	}
	else
	{
		frame2Pos.y += speed * dt;
		frame[1].SetPosition(frame2Pos);
		if (frame2Pos.y >= 800.f)
		{
			frame2Pos.y = 800.f;
			frame[1].SetPosition(frame2Pos);
		}
	}
	if (InputMgr::GetKey(sf::Keyboard::Num3))
	{
		frame3Pos.y -= speed * dt;
		frame[2].SetPosition(frame3Pos);
		if (frame3Pos.y <= 500.f)
		{
			frame3Pos.y = 500.f;
			frame[2].SetPosition(frame3Pos);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Space) && handBullet == 0)
		{
			handBullet = frameBullet[2];
			frameBullet[2] = 0;
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Space) && handBullet > 0)
		{
			frameBullet[2] = handBullet;
			handBullet = 0;
		}
	}
	else
	{
		frame3Pos.y += speed * dt;
		frame[2].SetPosition(frame3Pos);
		if (frame3Pos.y >= 800.f)
		{
			frame3Pos.y = 800.f;
			frame[2].SetPosition(frame3Pos);
		}
	}
	if (InputMgr::GetKey(sf::Keyboard::Num4))
	{
		frame4Pos.y -= speed * dt;
		frame[3].SetPosition(frame4Pos);
		if (frame4Pos.y <= 500.f)
		{
			frame4Pos.y = 500.f;
			frame[3].SetPosition(frame4Pos);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Space) && handBullet == 0)
		{
			handBullet = frameBullet[3];
			frameBullet[3] = 0;
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Space) && handBullet > 0)
		{
			frameBullet[3] = handBullet;
			handBullet = 0;
		}
	}
	else
	{
		frame4Pos.y += speed * dt;
		frame[3].SetPosition(frame4Pos);
		if (frame4Pos.y >= 800.f)
		{
			frame4Pos.y = 800.f;
			frame[3].SetPosition(frame4Pos);
		}
	}
	magazinePos.x = (handFrame.GetGlobalBounds().left + handFrame.GetGlobalBounds().width);
	magazinePos.y = (handFrame.GetGlobalBounds().top + handFrame.GetGlobalBounds().height);
	handMagazine.SetPosition(magazinePos);

	for (int i = 0; i < 4; ++i)
	{
		frameMagazinePos = frame[i].GetPosition();
		magazine[i].SetPosition({ frameMagazinePos.x + 85.f,frameMagazinePos.y + 120.f });
	}

	if (handBullet > 0)
	{
		if (handFramePos.y >= 600.f)
		{
			handFramePos.y -= speed * dt;
			if (handFramePos.y <= 600)
			{
				handFramePos.y = 600.f;
			}
		}
		handFrame.SetPosition(handFramePos);
		handMagazine.SetTexture("graphics/fullmagazine.png");
		handMagazine.SetActive(true);
		uiMsg->GetHandBullet(true);
	}
	else if(handBullet <= 0)
	{
		if (handFramePos.y <= 800.f)
		{
			handFramePos.y += speed * dt;
		}
		else if (handFramePos.y >= 800.f)
		{
			handFramePos.y = 800.f;
		}
		handFrame.SetPosition(handFramePos);
		handMagazine.SetTexture("graphics/emptymagazine.png");
		handMagazine.SetActive(false);
		uiMsg->GetHandBullet(false);
	}

}

void UiHud::Init()
{
	uiMsg = new UiMsg("uiMsg");

	for (int i = 0; i < 4; ++i)
	{
		frame[i].Init();
		magazine[i].Init();
		frame[i].SetScale({ 2.f,2.f });
		frame[i].SetOrigin(Origins::TL);
		frame[i].SetPosition({ -300.f + i * 200.f, 800.f });
		frameBullet[i] = 6;
	}

	handFrame.Init();
	handMagazine.Init();

	frame[0].SetTexture("graphics/inventoryFrame1.png");
	frame[1].SetTexture("graphics/inventoryFrame2.png");
	frame[2].SetTexture("graphics/inventoryFrame3.png");
	frame[3].SetTexture("graphics/inventoryFrame4.png");

	handFrame.SetTexture("graphics/inventoryFrame.png");
	handMagazine.SetTexture("graphics/emptymagazine.png");



	for (int i = 0; i < 4; ++i)
	{
		magazine[i].SetTexture("graphics/fullmagazine.png");
		magazine[i].SetScale({ 1.8f,1.8f });
		magazine[i].SetOrigin(Origins::MC);
		magazine[i].SetPosition({ 0.f,0.f });
	}

	handFrame.SetScale({ 2.f,2.f });
	handMagazine.SetScale({ 2.f,2.f });

	handFrame.SetOrigin(Origins::TL);
	handMagazine.SetOrigin(Origins::BR);

	handFrame.SetPosition(handFramePos);
	handMagazine.SetPosition({ 0.f,0.f });

	speed = 1500.f;

	gun = new Gun("gun");
}

void UiHud::Reset()
{
	GameObject::Reset();

	for (int i = 0; i < 4; ++i)
	{
		frame[i].Reset();
		magazine[i].Reset();
		magazine[i].Reset();
		frameBullet[i] = 6;
	}
	uiMsg = dynamic_cast<UiMsg*>(SCENE_MGR.GetCurrentScene()->FindGo("uiMsg"));
}

void UiHud::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	for (int i = 0; i < 4; ++i)
	{
		frame[i].Draw(window);
		if (frameBullet[i] > 0)
		{
			magazine[i].Draw(window);
		}

	}

	handFrame.Draw(window);
	if (handBullet > 0)
	{
		handMagazine.Draw(window);
	}

}

void UiHud::SetHandMagazine(int i)
{
	handBullet = i;
}


