#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	Pingpong,
};

struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;

	AnimationFrame(const std::string& id, const sf::IntRect& coord)
		:textureId(id), texCoord(coord)
	{
	}

	const sf::Texture& GetTexture() const
	{
		return RES_MGR_TEXTURE.Get(textureId);
	}
};

struct AnimationClip
{
	std::string id;
	int fps = 30;
	AnimationLoopTypes loopType = AnimationLoopTypes::Single;
	std::vector<AnimationFrame>frames;

	int GetTotalFrame() const
	{
		return frames.size();
	}

	bool loadFromFile(const std::string& filePath);
};

struct AnimationEvent
{
	std::string clipId;
	int frame = 0;
	std::function<void()> action;
};

class Animator
{
protected:
	std::queue<std::string> queue;
	std::list<AnimationEvent> eventList;

	float speed = 1.f;

	bool isPlaying = false;
	AnimationClip* currentClip;
	int totalFrame = 0;
	int currentFrame = -1;
	int addFrame = 1;
	float clipDuration = 0.f;

	float accunTime = 0,f;

	sf::Sprite* target = nullptr;

public:
	Animator();
	~Animator();

	void AddEvent(const std::string& clipId, int frame, std::function<void()>action);
	void ClearEvent();

	bool IsPlaying() const { return isPlaying; }
	const std::string& GetCurrentClipId() { return currentClip->id; }

	sf::Sprite* GetTarget() const { return target; }
	void SetTarget(sf::Sprite* t) { target = t; }

	float GetSpeed() const { return speed; }
	float SetSpeed(float s) { speed = s; }

	void Update(float dt);

	void Play(const std::string& clipId, bool clearQueue = true);
	void PlayQueue(const std::string& clipid);
	void Stop();
	void SetFrame(const AnimationFrame& frame);
};

