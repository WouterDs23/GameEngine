#pragma once
#include "GameObject.h"
#include "TextComponent.h"

class Commands
{
public:
	Commands();
	virtual ~Commands();
	virtual bool execute(std::weak_ptr<dae::GameObject> actor);
};
class JumpCommand : public Commands
{
public:
	virtual bool execute(std::weak_ptr<dae::GameObject> actor) override
	{
		if (actor.lock())
		{
			auto comp = actor.lock()->GetComponent<TextComponent>().lock();
			if (comp)
			{
				comp->SetText("Wouter");
			}
		}		
		std::cout << "Jump" << std::endl; return false;
	}
};

class FireCommand : public Commands
{
public:
	virtual bool execute(std::weak_ptr<dae::GameObject>) override { std::cout << "Fire" << std::endl; return false; }
};

class DuckCommand : public Commands
{
public:
	virtual bool execute(std::weak_ptr<dae::GameObject>) override { std::cout << "Duck" << std::endl; return false; }
};

class ExitCommand : public Commands
{
public:
	virtual bool execute(std::weak_ptr<dae::GameObject>) override { std::cout << "Exit" << std::endl; return true; }
};