#ifndef VECTOR_PROPERTY_H
#define VECTOR_PROPERTY_H

namespace KI
{

class VectorProperty : public IModelProperty
{
public:
	VectorProperty(const vector<vec3>& vectorList, const vec3& color);
	~VectorProperty();

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_VECTOR; }
	virtual void Draw();
	virtual void Update(void* model);
private:
	void GenVBO(const vector<vec3>& vertexList, const vec3& color);
	shared_ptr<IShader> m_pShader;
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
	
};

}


#endif // !VECTOR_PROPERTY_H

