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
	GameObject::Init();
	gunBody.Init();


	gunBody.SetTexture("graphics/gunBody.png");
	gunBody.SetOrigin(Origins::BL);
	gunBody.SetPosition({ 0.f,0.f });

}

void UiHud::Reset()
{
	GameObject::Reset();
	gunBody.Reset();
}

void UiHud::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	gunBody.Draw(window);
}
