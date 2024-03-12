#pragma once
#include "GameObject.h"
#include "TextGo.h"

class Gun;

class UiMsg : public GameObject
{
protected:
	TextGo uiMsg[11];
	TextGo uiConcentration;
	TextGo discovered;
	TextGo uiHp;
	Gun* gun;

	int bullet = 0;
	bool handBullet = true;
	bool OnRmc = false;
	bool OnKeyS = false;
	bool OnKeyE = false;
	bool OnKeyE_T = false;
	bool DisCover = false;
	bool emptyGun = false;
	int concent = 100;
	int hp = 100;
public:
	UiMsg(const std::string& name = "");
	~UiMsg() override = default;

	TextGo GetuiMsg()
	{
		for (int i = 0; i <= 9; ++i)
		{
			return uiMsg[i];
		}
	}

	void Init() override;
	void Reset()override;
	void Update(float dt)override;
	void Draw(sf::RenderWindow& window) override;

	void GetBullet(int i) { bullet = i; }
	void GetRmc(bool b) { OnRmc = b; }
	void GetKeyS(bool b) { OnKeyS = b; }
	void GetKeyE(bool b) { OnKeyE = b; }
	void uiUpdate();
	void UiConcent(int i) { concent = i; }
	void GetKeyE_T(bool b) { OnKeyE_T = b; }
	void GetDisCover(bool b) { DisCover = b; }
	void GetHandBullet(bool b) { handBullet = b; }
	void GetEmptyGun(bool b) { emptyGun = b; }
};

