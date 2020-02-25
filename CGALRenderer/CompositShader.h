#ifndef COMPOSIT_SHADERL_H
#define COMPOSIT_SHADERL_H

namespace KI
{

class CompositUniform;
class CompositShaderDefine;
class CompositShader : public IShader
{
public:
	enum COMPOSIT_TYPE
	{
		COMPOSIT_TYPE_ADD,
		COMPOSIT_TYPE_SUB,
		COMPOSIT_TYPE_MULT,
		COMPOSIT_TYPE_OVERWRITE,
		COMPOSIT_TYPE_NUM
	};
	enum COMPOSIT_UNIFORM : unsigned short
	{
		COMPOSIT_UNIFORM_SOURCE_TEXTURE,
		COMPOSIT_UNIFORM_TARGET_TEXTURE,
		COMPOSIT_UNIFORM_NUM
	};

	CompositShader();
	~CompositShader();
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_COMPOSIT; }

	virtual void Initialize() override;
	virtual void FetchUniformLocation() override;
	virtual void Bind(shared_ptr<IUniform> uniform) override;
	virtual void UnBind() override;

private:
	shared_ptr<CompositUniform> m_uniformParameter;
};

class CompositUniform : public IUniform
{
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_COMPOSIT; }
	shared_ptr<Texture> m_pSource;
	shared_ptr<Texture> m_pDestination;
};

class CompositShaderDefine : public IShaderDefine
{
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_COMPOSIT; };
	void SetShaderDefine(CompositShader::COMPOSIT_TYPE type);
	virtual void GetVertexDefine(string& define) {};
	virtual void GetFragDefine(string& define);
	virtual bool Compare(IShaderDefine* shaderDefine);

	CompositShader::COMPOSIT_TYPE m_CompositType;
};


#define FRAG_SHADER_COMPOSIT_ADD		"#define COMPOSIT_ADD\n"
#define FRAG_SHADER_COMPOSIT_SUB		"#define COMPOSIT_SUB\n"
#define FRAG_SHADER_COMPOSIT_MULT		"#define COMPOSIT_MULT\n"
#define FRAG_SHADER_COMPOSIT_OVERWRITE	"#define COMPOSIT_OVERWRITE\n"
}

#endif COMPOSIT_SHADERL_H
