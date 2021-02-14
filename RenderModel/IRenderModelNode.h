#ifndef IRENDER_MODEL_NODE_H
#define IRENDER_MODEL_NODE_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT IRenderModelNode : public IModelNode
{
public:
	IRenderModelNode(shared_ptr<Scene> scene) :IModelNode(scene) {};
	IRenderModelNode(shared_ptr<Scene> scene, shared_ptr<IModel> model) :IModelNode(scene,model) {};

	~IRenderModelNode() {};
	virtual void InitializeUI() {};
	virtual void ShowUI() {}
	void VisibleProperty(PROPERTY_TYPE type, bool visible);
private:
};

}
}
#endif IRENDER_MODEL_NODE_H