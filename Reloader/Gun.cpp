#include "pch.h"
#include "Gun.h"

Gun::Gun(const std::string& name)
	:SpriteGo(name)
{
}

Gun::~Gun()
{
}

void Gun::TestInstance()
{
	isFiring = false;
	if (!isFiring)
	{
		animator.Play("animations/Gunreturn.csv");
		isFiring = true;
	}

}

void Gun::Init()
{
	SpriteGo::Init();
	animator.SetTarget(&sprite);
}

void Gun::Reset()
{
	animator.ClearEvent();

	std::function<void()> funcInstance = std::bind(&Gun::TestInstance, this);
	animator.AddEvent("animations/Gun.csv", 5, funcInstance);

	animator.Play("animations/Gun.csv");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f,0.f });
	bullet = 6;
}

void Gun::Update(float dt)
{
	animator.Update(dt);

	if (isFiring && InputMgr::GetMouseButtonDown(sf::Mouse::Left) && bullet > 0)
	{
		animator.Play("animations/Gun.csv");
		std::cout << "shhot" << std::endl;
		bullet -= 1;
		if (bullet <= 0)
		{
			bullet = 0;
		}
	}

	SetPosition(position);

	SpriteGo::Update(dt);
	
}
