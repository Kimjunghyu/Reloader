#pragma once
#include "SpriteGo.h"
class Cartridge : public SpriteGo
{
protected:


public:
	Cartridge(const std::string& name = "");
	~Cartridge()override = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

