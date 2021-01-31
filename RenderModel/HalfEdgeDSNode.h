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

	virtual void ShowUI() override;
private:
	struct UI
	{
		UI() : visibleHalfEdge(false), visibleResolution(false), visibleBVH(false), visibleTangent(false){}
		bool visibleHalfEdge;
		bool visibleResolution;
		bool visibleBVH;
		bool visibleTangent;
		bool calcAlignment;
	};

	UI m_ui;
};
}
}

#endif HALFEDGE_DS_NODE_H
