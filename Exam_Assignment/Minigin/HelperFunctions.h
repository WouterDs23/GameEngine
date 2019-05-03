#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
inline float SqrtMagnitude(glm::vec3 obj)
{
	return obj.x * obj.x + obj.y * obj.y;
}
inline float Magnitude(glm::vec3 obj)
{
	return sqrtf(SqrtMagnitude(obj));
}
inline float Normalize(glm::vec3& obj)
{
	const float magnitude = Magnitude(obj);
	if (!bool(abs(magnitude - 0.f) > FLT_EPSILON))
	{
		return 0.f;
	}
	float tempVal = 1.f / magnitude;
	obj.x *= tempVal;
	obj.y *= tempVal;
	return magnitude;
}
inline glm::vec3 DistanceBetween2Objects(glm::vec3 obj, glm::vec3 obj2)
{
	glm::vec3 distance = obj - obj2;
	distance.x = abs(distance.x);
	distance.y = abs(distance.y);
	return distance;
}