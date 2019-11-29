#ifndef IMODEL_NODE_H
#define IMODEL_NODE_H
namespace KI
{
class IObserver;
class IModelNode : public IObserver
{
public:
	IModelNode() {};
	~IModelNode() {};

	virtual void ShowProperty() = 0;
	virtual void Draw() = 0;
	virtual void Update(void* sender, shared_ptr<EventArgs> args) {};
	virtual void AddTexture(shared_ptr<Texture> texture) {};

private:
};
}
#endif IMODEL_NODE_H