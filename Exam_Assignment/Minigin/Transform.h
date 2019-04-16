#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Transform final
	{
		glm::vec3 m_Position;
		glm::vec3 m_Size;
		glm::vec3 m_MiddlePos;
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);

		const glm::vec3& GetMiddlePosition();

		const glm::vec3& GetSize() const { return m_Size; }
		void SetSize(float x, float y, float z);
	};
}
