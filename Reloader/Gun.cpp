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

void Gun::EmptyMagazine()
{
	animator.Stop();
	if (bulletCount != 0)
	{
		animator.Resume();
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
	bulletCount = 6;
}

void Gun::Update(float dt)
{
	animator.Update(dt);
	timer += dt;
	if (isFiring && InputMgr::GetMouseButtonDown(sf::Mouse::Left) && timer >= fireinterval)
	{
		animator.Play("animations/Gun.csv");
		std::cout << "fire" << std::endl;
		bulletCount -= 1;
		std::cout << bulletCount << std::endl;
		timer = 0;
	}
	if (bulletCount <= 0)
	{
		std::function<void()> emptybullet = std::bind(&Gun::EmptyMagazine, this);
		animator.AddEvent("animations/Gunreturn.csv", 1, emptybullet);
		bulletCount = 0;
		isFiring = false;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		bulletCount = 6;
		isFiring = true;
		animator.Resume();
	}

	SpriteGo::Update(dt);
	
}
