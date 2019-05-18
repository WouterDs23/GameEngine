#include "MiniginPCH.h"
#include "Commands.h"
#include "GameObject.h"
#include "../DigDug/CharacterComponent.h"
#include "AIComponent.h"

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
		auto comp = actor.lock()->GetComponent<dae::CharacterComponent>().lock();
		if (comp)
		{
			comp->MoveLeft();
		}
		else
		{
			auto ai = actor.lock()->GetComponent<dae::AIComponent>().lock();
			if (ai)
			{
				ai->MoveLeft();
			}
		}
	}
	return false;
}

bool dae::MoveRight::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto comp = actor.lock()->GetComponent<dae::CharacterComponent>().lock();
		if (comp)
		{
			comp->MoveRight();
		}
		else
		{
			auto ai = actor.lock()->GetComponent<dae::AIComponent>().lock();
			if (ai)
			{
				ai->MoveRight();
			}
		}
	}
	return false;
}

bool dae::MoveUp::execute(std::weak_ptr<dae::GameObject> actor)
{
	{
		if (actor.lock())
		{
			auto comp = actor.lock()->GetComponent<dae::CharacterComponent>().lock();
			if (comp)
			{
				comp->MoveUp();
			}
			else
			{
				auto ai = actor.lock()->GetComponent<dae::AIComponent>().lock();
				if (ai)
				{
					ai->MoveUp();
				}
			}
		}
		return false;
	}
}

bool dae::MoveDown::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto comp = actor.lock()->GetComponent<dae::CharacterComponent>().lock();
		if (comp)
		{
			comp->MoveDown();
		}
		else
		{
			auto ai = actor.lock()->GetComponent<dae::AIComponent>().lock();
			if (ai)
			{
				ai->MoveDown();
			}
		}
	}
	return false;
}
