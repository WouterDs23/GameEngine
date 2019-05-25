#include "MiniginPCH.h"
#include "ScoreObserver.h"


void ScoreObserver::onNotify(const std::weak_ptr<dae::GameObject> object)
{
	if (object.lock())
	{
		Kills++;
		auto pooka = object.lock()->GetComponent<Enemies::PookaComponent>();
		if (pooka.lock())
		{
			Unlock(object, std::make_shared<PookaScore>());
		}
		auto rock = object.lock()->GetComponent<Environment::RockComponent>();
		if (rock.lock())
		{
			Unlock(object, std::make_shared<RockScore>());
		}
		auto fygar = object.lock()->GetComponent<Enemies::FygarComponent>();
		if (fygar.lock())
		{
			Unlock(object, std::make_shared<FygarScore>());
		}
		//RockScore::m_Kills++;
		
	}
}
