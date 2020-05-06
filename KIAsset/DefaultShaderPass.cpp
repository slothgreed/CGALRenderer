namespace KI
{
namespace Asset
{
DefaultShaderPass::DefaultShaderPass()
{
	auto pVertexUniform = make_shared<DefaultVertexUniform>();
	auto pFragUniform = make_shared<DefaultFragUniform>();
	GetUniform()->Set(pVertexUniform, pFragUniform);
}

DefaultShaderPass::~DefaultShaderPass()
{

}

void DefaultShaderPass::AddTexture(shared_ptr<Texture> texture)
{
	if (GetUniform()->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		assert(0);
		return;
	}

	auto uniform = static_pointer_cast<DefaultFragUniform>(GetUniform()->Frag());
	uniform->SetTexture(texture);
}

void DefaultShaderPass::SetFixColor(const vec4& color)
{
	if (GetUniform()->Vertex()->Type() != SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		assert(0);
		return;
	}

	auto uniform = static_pointer_cast<DefaultVertexUniform>(GetUniform()->Vertex());
	uniform->SetFixColor(color);
}

void DefaultShaderPass::VisibleNormal(bool visible)
{
	if (GetUniform()->Vertex()->Type() != SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		assert(0);
		return;
	}

	auto uniform = static_pointer_cast<DefaultVertexUniform>(GetUniform()->Vertex());
	uniform->VisibleNormal(visible);

	m_bReCompileShader = true;
}

void DefaultShaderPass::CompileShader(IVertexBuffer* pVertexBuffer)
{
	if (pVertexBuffer->Type() == VERTEX_BUFFER_TYPE::VERTEX_BUFFER_TYPE_DEFAULT)
	{
		auto pDefaultBuffer = (DefaultVertexBuffer*)(pVertexBuffer);
		auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_DEFAULT);
		auto pVertexCode = make_shared<DefaultVertexCode>();
		pVertexCode->SetShaderDefine(pDefaultBuffer->Layout());
		auto uniform = static_pointer_cast<DefaultVertexUniform>(GetUniform()->Vertex());
		pVertexCode->SetViewNormal(uniform->VisibleNormal());
		pBuildInfo->SetVertexCode(pVertexCode);
		auto pFragCode = make_shared<DefaultFragCode>();
		pFragCode->SetShaderDefine(pDefaultBuffer->Layout());
		pBuildInfo->SetFragCode(pFragCode);
		SetShader(ShaderManager::Instance()->FindOrNew(pBuildInfo));
	}
	else
	{
		assert(0);
	}
}

bool DefaultShaderPass::Compare(const IShaderPass& material)
{
	if (material.Type() == MATERIAL_TYPE_DEFAULT)
	{
		assert(0);
		// todo : compare;
	}

	return false;
}
}
}