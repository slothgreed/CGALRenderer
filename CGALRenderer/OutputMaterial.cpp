namespace KI
{

OutputMaterial::OutputMaterial()
{
}

OutputMaterial::~OutputMaterial()
{
}

void OutputMaterial::CompileShader()
{
	if (m_pVertexBuffer->Type() == DefaultVertexBuffer::DefaultVertexBufferTypeStr)
	{
		auto pDefaultBuffer = static_pointer_cast<DefaultVertexBuffer>(m_pVertexBuffer);
		if (pDefaultBuffer->Layout() != VERTEX_LAYOUT::VERTEX_LAYOUT_PT)
		{
			assert(0);
		}

		auto shaderDefine = make_shared<OutputShaderDefine>();
		m_pShader = ShaderManager::Instance()->FindOrNew(shaderDefine);
	}
	else
	{
		assert(0);
	}
}

void OutputMaterial::AddColorTexture(shared_ptr<Texture> colorTexture)
{
	m_pColorTexture = colorTexture;

}

void OutputMaterial::Bind()
{
	auto pUniform = make_shared<OutputUniform>();
	pUniform->pTexture = m_pColorTexture;
	m_pShader->Bind(pUniform);
}

void OutputMaterial::UnBind()
{
	m_pShader->UnBind();
}

bool OutputMaterial::Compare(const IMaterial& material)
{
	if (material.Type() == MATERIAL_TYPE_OUTPUT_BUFFER)
	{
		return true;
	}

	return false;
}
}