#pragma once
#include "BaseComponent.h"
namespace dae
{
	class GhostComponent final : public BaseComponent
	{
	public:
		GhostComponent();
		~GhostComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		void EnableGhostMode(bool enable = true);

		bool GetInGhostForm() const { return m_InGhostForm; }

		GhostComponent(const GhostComponent& other) = delete;
		GhostComponent(GhostComponent&& other) noexcept = delete;
		GhostComponent& operator=(const GhostComponent& other) = delete;
		GhostComponent& operator=(GhostComponent&& other) noexcept = delete;
	private:
		bool m_InGhostForm;
	};
}
