#ifndef CUBE_H
#define CUBE_H

namespace KI
{
namespace Topology
{
class DLL_EXPORT CubeArgs
{
public:
	enum PrimitiveType
	{
		TRIANGLES,
		LINES,
	};
	CubeArgs() : m_min(), m_max(){};
	CubeArgs(vec3 min, vec3 max) :m_min(min), m_max(max), m_primType(CubeArgs::PrimitiveType::TRIANGLES) {};
	CubeArgs(vec3 min, vec3 max, PrimitiveType type);
	~CubeArgs() {};
	vec3 m_min;
	vec3 m_max;
	PrimitiveType m_primType;
};
class DLL_EXPORT Cube : public IPrimitive
{
public:
	Cube(int indexOffset);
	Cube();
	~Cube();

	void Build(const CubeArgs& args);
private:
	void AddTrianlgeIndexFromRectangle(int index, int vertex0, int vertex1, int vertex2, int vertex3);

};
}
}
#endif CUBE_H
