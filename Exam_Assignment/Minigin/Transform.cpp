#include "MiniginPCH.h"
#include "Transform.h"

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

const glm::vec3& dae::Transform::GetMiddlePosition()
{
	m_MiddlePos = {m_Position.x + m_Size.x / 2.f, m_Position.y + m_Size.y / 2.f, 0};
	return m_MiddlePos;
}

void dae::Transform::SetSize(float x, float y, float z)
{
	m_Size.x = x;
	m_Size.y = y;
	m_Size.z = z;
}
