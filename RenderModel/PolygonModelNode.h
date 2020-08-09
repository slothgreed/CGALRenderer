#ifndef MODEL_NODE_H
#define MODEL_NODE_H
namespace KI
{
namespace RenderModel
{
class DLL_EXPORT PolygonModelNode : public IModelNode
{
public:
	PolygonModelNode(shared_ptr<IModel> model);
	~PolygonModelNode();
	virtual void ShowProperty() override;
	virtual void Update(void* sender, IEventArgs* args) override;
	IPolygonModel* GetModel();


	void VisibleBDB(bool visibility);
	void VisibleNormal(bool visibility);
	void VisibleFace(bool visibility);
	void VisibleEdge(bool visibility);
	void AddPartSelect(TOPOLOGY_TYPE type, int first, int count);
	shared_ptr<IVertexBuffer> GetVertexBuffer();
protected:
	string m_name;

private:
	BDB m_bdb;
	void SetRenderData();
};
}
}

#endif MODEL_NODE_H
