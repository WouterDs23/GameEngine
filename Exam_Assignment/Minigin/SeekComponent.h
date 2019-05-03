#pragma once
#include "BaseComponent.h"
#include "Commands.h"

namespace dae
{
	class GameObject;
	class SeekComponent final : public BaseComponent
	{
	public:
		SeekComponent();
		~SeekComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		void SetTarget(std::weak_ptr<GameObject> target) { m_Target = target; }

		std::vector< std::shared_ptr<GameObject>> FindPath();

		std::vector< std::shared_ptr<GameObject>> ConnectingObjects(const std::vector< std::shared_ptr<GameObject>> objects, const std::shared_ptr<GameObject> object);

		SeekComponent(const SeekComponent& other) = delete;
		SeekComponent(SeekComponent&& other) noexcept = delete;
		SeekComponent& operator=(const SeekComponent& other) = delete;
		SeekComponent& operator=(SeekComponent&& other) noexcept = delete;
	private:
		std::weak_ptr<GameObject> m_Target;
	};
}
