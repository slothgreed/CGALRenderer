#ifndef VERTEX_INDEX_PROPERTY_H
#define VERTEX_INDEX_PROPERTY_H

namespace KI
{
namespace RenderModel
{
class CameraNode;
class DLL_EXPORT VertexIndexPropertyArgs : public IPropertyArgs
{
public:

	VertexIndexPropertyArgs(CameraNode* pCameraNode):m_pCameraNode(pCameraNode){};
	~VertexIndexPropertyArgs() {};
	virtual PROPERTY_TYPE PropertyType() { return PROPERTY_TYPE_VERTEX_INDEX; };
	const CameraNode* Camera() const { return m_pCameraNode; }
private:
	CameraNode* m_pCameraNode;
};

// NOTE : By ImGui
class VertexIndexProperty : public IRenderModelProperty
{
public:
	VertexIndexProperty();
	~VertexIndexProperty();

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_VERTEX_INDEX; }
	virtual void BuildCore(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
private:
	void SetIndexText(IModelNode* pModelNode, const ICamera* pCamera);
	std::vector<NoWindowTextUI> m_indexText;
};

}
}

#endif // !VERTEX_INDEX_PROPERTY_H
