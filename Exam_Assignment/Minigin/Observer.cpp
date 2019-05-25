#include "MiniginPCH.h"
#include "Observer.h"
#include "Subject.h"

void dae::Observer::Attach(const std::weak_ptr<Subject> subject)
{	
	if (subject.lock())
	{
		subject.lock()->addObserver(shared_from_this());
	}
}
