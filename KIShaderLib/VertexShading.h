#ifndef VERTEX_SHADING_H
#define VERTEX_SHADING_H

namespace KI
{
namespace ShaderLib
{
enum VERTEX_SHADING_TYPE
{
	VERTEX_SHADING_POSITION,	// ���_�J���[
	VERTEX_SHADING_TEXCOORD,	// �e�N�X�`���F
	VERTEX_SHADING_COLOR,		// ���_�J���[
	VERTEX_SHADING_NORMAL,		// �@���J���[
	VERTEX_SHADING_DEPTH,		// �f�v�X
};

// no shading
class DLL_EXPORT VertexShading : public IShading
{
public:
	VertexShading(VERTEX_SHADING_TYPE type);
	~VertexShading();

	VERTEX_SHADING_TYPE Type() { return m_Type; }

	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) override;

private:
	bool Compare(IShading* pShading);
	VERTEX_SHADING_TYPE m_Type;

};

class DLL_EXPORT VertexShadingVertexCode : public DefaultVertexCode
{
public:

	VertexShadingVertexCode(VERTEX_SHADING_TYPE type);
	~VertexShadingVertexCode() {};

	virtual void Initialize(GLuint programId) {};
	virtual void SetViewVertexType(VERTEX_SHADING_TYPE type) { m_Type = type; }
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override {};
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override {};

	VERTEX_SHADING_TYPE Type() { return m_Type; }
private:
	VERTEX_SHADING_TYPE m_Type;
};

class DLL_EXPORT VertexShadingFragCode : public IShaderCode
{
public:

	VertexShadingFragCode();
	~VertexShadingFragCode() {};

	virtual void Initialize(GLuint programId) {};
	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)  override {};
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)  override {};

private:
	VERTEX_SHADING_TYPE m_Type;
};
}
}

#endif VERTEX_SHADING_H
