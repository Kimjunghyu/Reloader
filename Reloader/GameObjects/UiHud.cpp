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
}

void UiHud::Init()
{
	frame1.Init();
	frame2.Init();
	frame3.Init();
	frame4.Init();

	frame1.SetTexture("graphics/inventoryFrame1.png");
	frame2.SetTexture("graphics/inventoryFrame2.png");
	frame3.SetTexture("graphics/inventoryFrame3.png");
	frame4.SetTexture("graphics/inventoryFrame4.png");

	frame1.SetOrigin(Origins::TC);
	frame2.SetOrigin(Origins::TC);
	frame3.SetOrigin(Origins::TC);
	frame4.SetOrigin(Origins::TC);

	referenceResolution = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	frame1.SetPosition({ 25.f,referenceResolution.y - 25 });
	frame2.SetPosition({ 125.f,referenceResolution.y - 25 });
	frame3.SetPosition({ 225.f,referenceResolution.y - 25 });
	frame4.SetPosition({ 325.f,referenceResolution.y - 25 });
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
}
