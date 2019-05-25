#pragma once
namespace dae
{
	enum Event
	{
		
	};
	class GameObject;
	class Subject;
	class Observer : public std::enable_shared_from_this<Observer>
	{
	public:
		void Attach(const std::weak_ptr<Subject> subject);
		virtual ~Observer() = default;
		virtual void onNotify(const std::weak_ptr<GameObject> object) = 0;
	};
}
