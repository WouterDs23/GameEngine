#include "MiniginPCH.h"
#include "Commands.h"
#include "GameObject.h"
#include "CharacterComponent.h"

dae::Commands::Commands()
{

}

dae::Commands::~Commands()
{

}

bool dae::Commands::execute(std::weak_ptr<dae::GameObject> actor)
{
	return false;
}

bool dae::MoveLeft::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto comp = actor.lock()->GetComponent<CharacterComponent>().lock();
		if (comp)
		{
			comp->MoveLeft();
		}
	}
	return false;
}

bool dae::MoveRight::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto comp = actor.lock()->GetComponent<CharacterComponent>().lock();
		if (comp)
		{
			comp->MoveRight();
		}
	}
	return false;
}

bool dae::MoveUp::execute(std::weak_ptr<dae::GameObject> actor)
{
	{
		if (actor.lock())
		{
			auto comp = actor.lock()->GetComponent<CharacterComponent>().lock();
			if (comp)
			{
				comp->MoveUp();
			}
		}
		return false;
	}
}

bool dae::MoveDown::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto comp = actor.lock()->GetComponent<CharacterComponent>().lock();
		if (comp)
		{
			comp->MoveDown();
		}
	}
	return false;
}
