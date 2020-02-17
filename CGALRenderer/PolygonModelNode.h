#ifndef MODEL_NODE_H
#define MODEL_NODE_H
namespace KI
{
class IModelNode;
class IShader;
class IVertexBuffer;
class IModelProperty;
class IMaterial;
class PolygonModelNode : public IModelNode
{
public:
	PolygonModelNode(shared_ptr<IModel> model);
	~PolygonModelNode();
	virtual void Draw() override;
	virtual void ShowProperty() override;
	virtual void Update(void* sender, shared_ptr<EventArgs> args) override;
	IPolygonModel* GetModel();

	void VisibleBDB(bool visibility);
	void VisibleNormal(bool visibility);
protected:
	string m_name;
	shared_ptr<IMaterial> m_pFaceMaterial;
	shared_ptr<IMaterial> m_pEdgeMaterial;

private:
	BDB m_bdb;
	void SetRenderData();
};

}

#endif MODEL_NODE_H
