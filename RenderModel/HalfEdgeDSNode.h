#ifndef HALFEDGE_DS_NODE_H
#define HALFEDGE_DS_NODE_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT HalfEdgeDSNode : public PolygonModelNode
{
public :
	HalfEdgeDSNode(shared_ptr<HalfEdgeModel> model);
	~HalfEdgeDSNode();
	static HalfEdgeDSNode* IsHalfEdgeDSNode(IModelNode* pModelNode);
	shared_ptr<ArrayBuffer> GetTangentBuffer();
	shared_ptr<ArrayBuffer> GetQuadPositionBuffer();
	void BuildTangentBuffer(const std::vector<vec3>& tangentBuffer);
	void BuildQuadPositionBuffer(const std::vector<vec3>& tangentBuffer);

	virtual void ShowUI() override;
private:
	struct UI
	{
		UI() : visibleHalfEdge(false), visibleResolution(false), visibleBVH(false), visibleParameter(false), visibleIndex(false),visibleSDF(false){}
		bool visibleHalfEdge;
		bool visibleResolution;
		bool visibleBVH;
		bool visibleSDF;
		bool visibleIndex;
		bool visibleParameter;
		bool calcAlignment;
		PlotLineUI plot;
	};

	shared_ptr<ArrayBuffer> m_pTangentBuffer;
	shared_ptr<ArrayBuffer> m_pQuadPositionBuffer;
	std::vector<float> m_orientateError;
	UI m_ui;
};
}
}

#endif HALFEDGE_DS_NODE_H
