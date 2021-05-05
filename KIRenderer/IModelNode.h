#ifndef IMODEL_NODE_H
#define IMODEL_NODE_H
namespace KI
{
namespace Renderer
{
class IModelProperty;
class RenderData;

class DLL_EXPORT PropertyIterator : IIterator<IModelProperty*>
{
public:
	PropertyIterator(IModelNode* pNode);

	virtual bool HasNext();
	virtual void Next();
	virtual IModelProperty* Current();

private:
	IModelNode*	m_pNode;
	int m_index;
};

class Scene;
class DLL_EXPORT IModelNode : public IObserver
{
public:
	friend class PropertyIterator;
	IModelNode();
	IModelNode(shared_ptr<IModel> model);
	virtual ~IModelNode();

	virtual void FixedShaderDraw(shared_ptr<IShader> pShader, shared_ptr<IShading> pShading, shared_ptr<UniformStruct> pUniformStorage);
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
	
	virtual void ClearSelect() {};
	virtual void AddSelect(PICK_TYPE type, shared_ptr<IShading> pShader, int index, int first, int count);
	virtual void Update(void* sender, IEventArgs* args);
	const shared_ptr<IModel> GetModel() { return m_pModel; }
	void SetModelMatrix(const mat4x4& matrix) { m_ModelMatrix = matrix; };
	const mat4x4& GetModelMatrix() const { return m_ModelMatrix; };
	void SetVisible(bool value) { m_visible = value; }
	bool Visible() { return m_visible; }
	virtual void SetPickID(int start, int* next);
	virtual bool HasPickID(int index);
	shared_ptr<RenderData> GetRenderData();
protected:
	void AddProperty(shared_ptr<IModelProperty> prop, IPropertyArgs* propArgs);
	bool HasProperty(unsigned int type);
	shared_ptr<IModelProperty> GetProperty(unsigned int type);
	void RemoveProperty(shared_ptr<IModelProperty> prop);
	virtual void DrawProperty(shared_ptr<UniformStruct> pUniform);
	virtual void UpdateProperty(void* sender, IEventArgs* args);
	shared_ptr<IModel> m_pModel;
	virtual void BindModel(shared_ptr<UniformStruct> pUniform);
	virtual void UnBindModel(shared_ptr<UniformStruct> pUniform);
	void SetRenderData(shared_ptr<RenderData> pRenderData);

private:

	shared_ptr<RenderData> m_pRenderData;
	bool m_visible;
	vector<shared_ptr<IModelProperty>> m_pProperty;
	mat4x4 m_ModelMatrix;
};
}
}
#endif IMODEL_NODE_H