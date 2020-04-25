#ifndef RAY_H
#define RAY_H

namespace KI
{
namespace Topology
{
class Ray
{
public:
	Ray() {};
	Ray(const vec3& origin, const vec3& direction) { Set(origin, direction); };
	~Ray() {};

	void Set(const vec3& origin, const vec3& direction) { m_origin = origin; m_direction = direction; }
	const vec3& Origin() const { return m_origin; };
	const vec3& Direction() const { return m_direction; };
private:
	vec3 m_origin;
	vec3 m_direction;
};
}
}

#endif RAY_H