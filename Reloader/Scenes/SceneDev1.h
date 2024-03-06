#pragma once

class AniTest2;

class SceneDev1 : public Scene
{
protected:
	AniTest2* anitest;
public:
	SceneDev1(SceneIds id);
	virtual ~SceneDev1();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};

