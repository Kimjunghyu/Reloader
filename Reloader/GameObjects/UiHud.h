#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Gun.h"

class UiHud : public GameObject
{
protected:
	SpriteGo frame1;
	SpriteGo frame2;
	SpriteGo frame3;
	SpriteGo frame4;
	SpriteGo handFrame;
	SpriteGo handMagazine;

	Gun* gun;

	float speed;

	sf::Vector2f direction = { 0.f, 0.f };
	TextGo uiFps;

	sf::Vector2f referenceResolution = { 1920.f, 1080.f };
	sf::Vector2f resolution = referenceResolution;

	sf::Vector2f frame1Pos;
	sf::Vector2f frame2Pos;
	sf::Vector2f frame3Pos;
	sf::Vector2f frame4Pos;
	sf::Vector2f magazinePos;

	int handBullet = 0;

public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;

	void SetResoultion(const sf::Vector2f resoution);

	void Update(float dt);

	void Init() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

	void SetHandMagazine(int i);
};

