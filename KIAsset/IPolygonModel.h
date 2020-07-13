#ifndef IPOLYGON_MODEL_H
#define IPOLYGON_MODEL_H
namespace KI
{
namespace Asset
{
class DLL_EXPORT IPolygonModel : public IModel, public IRaycastPick
{
public:
	IPolygonModel() {};
	virtual ~IPolygonModel() {};
	virtual void Load(const std::string& filePath) { assert(0); };
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal) { assert(0); };
	virtual void GetEdgeList(std::vector<vec3>& edgeList) { assert(0); };
	virtual void GetPositionList(std::vector<vec3>& position) { assert(0); };
	virtual bool HasVertexList() { return false; }
	virtual void GetVertexList(std::vector<Vertex>& vertex) { assert(0); };
	virtual void GetEdgeIndexList(std::vector<int>& index) { assert(0); };
	virtual void GetFaceIndexList(std::vector<int>& index) { assert(0); };
	virtual void GetBDB(BDB& bdb) = 0;
	virtual void RaycastPick(RaycastPickInfo& pickInfo) {};

	static bool IsPolygonModel(MODEL_TYPE type);
};
}
}
#endif IPOLYGON_MODEL_H