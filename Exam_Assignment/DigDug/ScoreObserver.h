#pragma once
#include "Observer.h"
#include "GameObject.h"
#include "PookaComponent.h"
#include "RockComponent.h"
#include "FygarComponent.h"
#include "MainCharComponent.h"
#include "ScoreKeeper.h"

class ScoreObserver : public dae::Observer
{
public:
	ScoreObserver() = default;
	~ScoreObserver() override = default;
	virtual void onNotify(const std::weak_ptr<dae::GameObject> object) override;
	static inline int Kills{};
private:
	void Unlock(const std::weak_ptr<dae::GameObject> object, std::shared_ptr<dae::Observer> score)
	{
		score->onNotify(object);
	}
	
};

class PookaScore final : public ScoreObserver
{
public:
	PookaScore() = default;
	~PookaScore() override = default;
	void onNotify(const std::weak_ptr<dae::GameObject> object) override
	{
		if (object.lock())
		{
			const auto pos = object.lock()->GetTransform().GetPosition();
			const int loc = int(pos.x / 32.f);
			if (loc < 6)
			{
				ScoreKeeper::GetInstance().AddScore(200);
				return;
			}
			if (loc < 11)
			{
				ScoreKeeper::GetInstance().AddScore(300);
			}
			if (loc < 15)
			{
				ScoreKeeper::GetInstance().AddScore(400);
			}
			if (loc < 19)
			{
				ScoreKeeper::GetInstance().AddScore(500);
			}
		}
	}
};

class RockScore final : public ScoreObserver
{
public:
	RockScore() = default;
	~RockScore() override = default;
	void onNotify(const std::weak_ptr<dae::GameObject>) override
	{
		switch (Kills)
		{
		case 1:
			ScoreKeeper::GetInstance().AddScore(1000);
			break;
		case 2:
			ScoreKeeper::GetInstance().AddScore(2500);
			break;
		case 3:
			ScoreKeeper::GetInstance().AddScore(4000);
			break;
		case 4:
			ScoreKeeper::GetInstance().AddScore(6000);
			break;
		case 5:
			ScoreKeeper::GetInstance().AddScore(8000);
			break;
		case 6:
			ScoreKeeper::GetInstance().AddScore(10000);
			break;
		case 7:
			ScoreKeeper::GetInstance().AddScore(12000);
			break;
		case 8:
			ScoreKeeper::GetInstance().AddScore(14000);
			break;
		default:
			break;
		}
	}
private:
	int m_Kills{};
};

class FygarScore final : public ScoreObserver
{
public:
	FygarScore() = default;
	~FygarScore() override = default;
	void onNotify(const std::weak_ptr<dae::GameObject> object) override
	{
		if (object.lock())
		{
			const auto pos = object.lock()->GetTransform().GetPosition();
			const int loc = int(pos.x / 32.f);
			if (loc < 6)
			{
				ScoreKeeper::GetInstance().AddScore(400);
				return;
			}
			if (loc < 11)
			{
				ScoreKeeper::GetInstance().AddScore(600);
			}
			if (loc < 15)
			{
				ScoreKeeper::GetInstance().AddScore(800);
			}
			if (loc < 19)
			{
				ScoreKeeper::GetInstance().AddScore(1000);
			}
		}
	}
};