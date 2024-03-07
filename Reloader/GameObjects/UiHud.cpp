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
	

}

void UiHud::Reset()
{
	GameObject::Reset();
}

void UiHud::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
}
