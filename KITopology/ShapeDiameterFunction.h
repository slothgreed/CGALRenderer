#ifndef SHAPE_DIAMETER_FUNCTION_HPP
#define SHAPE_DIAMETER_FUNCTION_HPP
namespace KI
{
namespace Topology
{
class DLL_EXPORT ShapeDiameterFunction
{
public:
	ShapeDiameterFunction();
	~ShapeDiameterFunction();

	void Calculate(
		float radius,
		int samplingNum,
		HalfEdgeDS* pHalfEdgeDS,
		std::vector<float>& value);

	const std::vector<vec3>& GetTestPos() { return m_testPos; }
	const Ray& GetRay() { return m_ray; }
	const Triangle& GetTri() { return m_triangle; }
	const std::vector<Triangle>& GetTarget() { return m_targetTri; }

private:

	// �v�Z�Ώۂ̖ʂ̒��o
	void ExtractMesh(
		const std::vector<HalfEdgeFace*>& pFaceList,
		std::vector<HalfEdgeFace*>& extract);
	
	// �_���T���v�����O
	void CreateRandomPoint(std::vector<vec4>& position);

	// �~���̒�ʌ����E�ʒu�ɕύX����
	void TransformPosition(const std::vector<vec4>& position, const vec3& center, const vec3& orient, std::vector<vec3>& circlePos);
	
	float CalculateSDF(
		HalfEdgeFace* pTarget,
		const std::vector<HalfEdgeFace*>& pFaceList,
		const std::vector<vec3>& circlePos);

	float m_radius;
	int m_samplingNum;

	std::vector<vec3> m_testPos;
	Ray m_ray;
	Triangle m_triangle;
	std::vector<Triangle> m_targetTri;

};

}
}

#endif SHAPE_DIAMETER_FUNCTION_HPP
