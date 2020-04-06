#ifndef NORMAL_PROPERTY_H
#define NORMAL_PROPERTY_H

namespace KI
{

// �@���v���p�e�B
class NormalProperty : public IModelProperty
{
public:
	NormalProperty();
	~NormalProperty();

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_VECTOR; }
	virtual void Draw();
	virtual void Update(IModelNode* pModelNode);
private:
	void Build(IModelNode* pModelNode);
	void SetVBOData(IModelNode* pModelNode);
	shared_ptr<IShader> m_pShader;
	shared_ptr<DefaultUniform> m_pUniform;
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	
};

}


#endif // !VECTOR_PROPERTY_H

