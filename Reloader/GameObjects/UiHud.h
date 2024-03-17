#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Gun.h"
#include "UiMsg.h"

class UiHud : public GameObject
{
protected:
	SpriteGo frame[4];
	SpriteGo handFrame;
	SpriteGo handMagazine;

	SpriteGo magazine[4];

	Gun* gun;
	UiMsg* uiMsg;

	float speed;

	sf::Vector2f direction = { 0.f, 0.f };

	sf::Vector2f handFramePos = { 850.f,600.f };
	sf::Vector2f frame1Pos;
	sf::Vector2f frame2Pos;
	sf::Vector2f frame3Pos;
	sf::Vector2f frame4Pos;
	sf::Vector2f magazinePos;
	sf::Vector2f frameMagazinePos;

	int handBullet = 0;
	int frameBullet[4] = { 6, 6, 6, 6 };

	bool onHandBullet = false;
public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;

	void Update(float dt);

	void Init() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

	void SetHandMagazine(int i);

	int GetHandBullet() {return handBullet;	}
};

