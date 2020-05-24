#ifndef BEZIER_LINE_NODE_H
#define BEZIER_LINE_NODE_H

namespace KI
{

class BezierLineNode : public IModelNode
{
public:
	BezierLineNode(shared_ptr<RenderData> pVertexBuffer);
	~BezierLineNode();

private:
	virtual void DrawCore() override;
	shared_ptr<BezierLineMaterial> m_pMaterial;
	shared_ptr<RenderData> m_pRenderData;
};
}

#endif BEZIER_LINE_NODE_H