#pragma once
#include "Observer.h"
#include <algorithm>
namespace dae
{
	class Observer;
	class Subject
	{
	public:
		void addObserver(std::shared_ptr<Observer> observer)
		{
			for (auto obs : m_Observers)
			{
				if (obs == observer)
				{
					std::cout << "Component is already in this object";
					return;
				}
			}
			m_Observers.push_back(observer);
		}
		void RemoveObserver(std::shared_ptr<Observer> observer)
		{
			m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer));
		}
		void Notify(const std::weak_ptr<dae::GameObject> object)
		{
			for (auto obs : m_Observers)
			{
				if (obs)
				{
					obs->onNotify(object);
				}
			}
		}
	private:
		std::vector<std::shared_ptr<Observer>> m_Observers;
	};
}
