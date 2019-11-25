#ifndef MATH_HELPER_H
#define MATH_HELPER_H
namespace KI
{
class MathHelper
{
public:
	MathHelper() {};
	~MathHelper() {};

	static void SphericalToCartesian(float x, float y, glm::vec3& result);
	static void CartesianToSpherical(const glm::vec3& position, float& radian, float& theta, float& phi);
	static float CalcTriangleArea(const vec3& v1, const vec3& v2, const vec3& v3); // counter cloclk wise
	static void CalcNormal(const vec3& v1, const vec3& v2, const vec3& v3, vec3& normal); // counter cloclk wise
	static float CalcRadian(const vec3& v1, const vec3& v2);
	static std::string ToString(const glm::vec3& value);
private:

};
}
#endif MATH_HELPER_H