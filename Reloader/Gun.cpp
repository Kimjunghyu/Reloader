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
-
	animator.Stop();

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

	bullet = new SpriteGo("bullet");
	bullet->SetTexture("graphics/bullet_0.png");
	bullet->SetPosition({ 0.f,0.f });
	bullet->SetOrigin(Origins::MC);
	bullet->sortLayer = 0;

}

void Gun::Reset()
{
	animator.ClearEvent();

	std::function<void()> funcInstance = std::bind(&Gun::TestInstance, this);
	animator.AddEvent("animations/Gun.csv", 5, funcInstance);

	animator.Play("animations/Gun.csv");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f,0.f });
	bulletCount = 6;
}

void Gun::Update(float dt)
{
	animator.Update(dt);

	if (isFiring && InputMgr::GetMouseButtonDown(sf::Mouse::Left) && bulletCount > 0)
	{
		animator.Play("animations/Gun.csv");
		std::cout << "fire" << std::endl;
		bulletCount -= 1;
		std::cout << bulletCount << std::endl;
		if (bulletCount <= 0)
		{
			bulletCount = 0;
		}
		bulletFiring.y = -300.f;
	}

	if (bulletCount <= 0)
	{
		std::function<void()> funcInstance = std::bind(&Gun::TestInstance, this);
		animator.AddEvent("animations/Gunreturn.csv", 1, funcInstance);
	}
	else
	{
		std::function<void()> funcInstance = std::bind(&Gun::TestInstance, this);
		animator.AddEvent("animations/Gunreturn.csv", 1, funcInstance);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		bulletCount = 6;
		isFiring = true;
		animator.Play("animations/Gunreturn.csv");
		animator.Resume();
	}

	bulletPos = bullet->GetPosition();
	bulletFiring.x = Direction.x * speed;
	bulletFiring.y += gravity * dt;
	bulletPos += bulletFiring * dt;
	bullet->SetPosition(bulletPos);
	SetPosition(position);

	SpriteGo::Update(dt);
	
}
