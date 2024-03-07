#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"

class UiHud : public GameObject
{
protected:
	SpriteGo fame1;
	SpriteGo fame2;
	SpriteGo fame3;
	SpriteGo fame4;

	TextGo uiFps;

	sf::Vector2f referenceResolution = { 1920.f, 1080.f };
	sf::Vector2f resolution = referenceResolution;

public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;

	void SetResoultion(const sf::Vector2f resoution);

	void Update(float dt);

	void Init() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;
};

