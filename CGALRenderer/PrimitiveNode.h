#ifndef PRIMITIVE_NODE_H
#define PRIMITIVE_NODE_H
namespace KI
{
class PrimitiveNode : public IModelNode
{
public:
	PrimitiveNode(shared_ptr<IShader> shader, shared_ptr<DefaultVertexBuffer> buffer);
	~PrimitiveNode();

	virtual void Draw();
	virtual void ShowProperty();
	virtual void Update(void* sender, shared_ptr<EventArgs> args);
private:
	string m_name;
	shared_ptr<IMaterial> m_pMaterial;
};
}

#endif PRIMITIVE_NODE_H