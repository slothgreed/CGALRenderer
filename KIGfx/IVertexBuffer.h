#ifndef IVERTEX_BUFFER_H
#define IVERTEX_BUFFER_H
#include <map>
namespace KI
{
namespace Gfx
{
class DLL_EXPORT IVertexBuffer
{
public:
	IVertexBuffer();
	~IVertexBuffer() {};

	virtual SHADER_TYPE Type() = 0;
	virtual void Add(GLuint location, shared_ptr<ArrayBuffer> arrayBuffer);
	virtual void Remove(GLuint location);
	virtual bool IsInstanceDraw() { return m_instanceNum > 1; };
	virtual void SetInstanceNum(int num) { m_instanceNum = num; }
	virtual void BindAttribDivisor() { assert(0); };
	virtual void UnBindAttribDivisor() { assert(0); };
	virtual void Draw(IndexBuffer* pIndexbuffer);
	virtual void Draw(GLuint primitiveType, GLuint first, GLuint count);
	virtual void Draw();
	void SetPrimitiveType(GLuint primitiveType);
	GLuint GetVertexSize() { return m_VertexSize; }
	void SetVertexSize(GLuint size) { m_VertexSize = size; }
	void Dispose();

protected:
	void BindToVAO(GLuint location);
	map<GLuint, shared_ptr<ArrayBuffer>> m_VertexInfo; // int = data location;
private:
	GLuint m_PrimitiveType;
	GLuint m_VertexSize;
	GLuint m_vaoId;
	GLuint m_instanceNum;
};
}
}
#endif IVERTEX_BUFFER_H
