#include "pch.h"
#include "Cartridge.h"

Cartridge::Cartridge(const std::string& name)
	:SpriteGo(name)
{
}

void Cartridge::Init()
{
	SpriteGo::Init();
}

void Cartridge::Reset()
{
	SpriteGo::Reset();
}

void Cartridge::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Cartridge::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
