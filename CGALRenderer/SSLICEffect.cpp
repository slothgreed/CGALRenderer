namespace KI
{
	
SSLICEffect::SSLICEffect()
{
}

SSLICEffect::~SSLICEffect()
{
}

void SSLICEffect::Initialize()
{
	int size = 64;
	TextureData textureData;
	TextureGenerator::RandomTexture(size,15, textureData);
	m_pNoizeTexture = make_shared<Texture>();
	m_pNoizeTexture->Generate();
	m_pNoizeTexture->Begin();
	m_pNoizeTexture->Set(textureData);
	m_pNoizeTexture->End();

	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, 256, 256);

	m_pPlaneBuffer = make_shared<DefaultVertexBuffer>();
	ModelGenerator::RenderPlane(m_pPlaneBuffer.get());

	auto shaderDefine = make_shared<DefaultShaderDefine>();
	shaderDefine->SetShaderDefine(VERTEX_LAYOUT_PT);
	m_pModelShader = static_pointer_cast<DefaultShader>(ShaderManager::Instance()->FindOrNew(shaderDefine));

	auto licshaderDefine = make_shared<SSLICShaderDefine>();
	m_pSSLICShader = static_pointer_cast<SSLICShader>(ShaderManager::Instance()->FindOrNew(licshaderDefine));

	TextureData blendTexture;
	blendTexture.width = 256;
	blendTexture.height = 256;
	m_pBlendTexture = make_shared<Texture>();
	m_pBlendTexture->Generate();
	m_pBlendTexture->Begin();
	m_pBlendTexture->Set(blendTexture);
	m_pBlendTexture->End();

	m_pModelUniform = make_shared<DefaultUniform>();
	m_pModelUniform->SetTexture(m_pBlendTexture);

	m_pSSLICUniform = make_shared<SSLICUniform>();
	m_pSSLICUniform->SetTexture(m_pBlendTexture);
}
void SSLICEffect::SetDrawModel(shared_ptr<DefaultVertexBuffer> model)
{
	m_pModel = model;
	if (m_pModel->HasTexCoord() == false)
	{
		Logger::Output(LOG_LEVEL::WARNING, "Need Texcoord.");
	}
}

void SSLICEffect::Draw()
{
	m_pModelShader->Use();
	m_pModelShader->Bind(m_pModelUniform);

	m_pModel->Draw();

	m_pModelShader->UnBind();
	m_pModelShader->UnUse();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);
	m_pSSLICShader->Use();
	m_pSSLICShader->Bind(m_pSSLICUniform);
	m_pPlaneBuffer->Draw();
	m_pSSLICShader->UnBind();
	m_pSSLICShader->UnUse();
	glDisable(GL_BLEND);

	m_pRenderTarget->CopyColorBuffer(0, m_pBlendTexture.get());
}

void SSLICEffect::Resize(int width, int height)
{

}


void SSLICEffect::ReadFromXML(const boost::property_tree::ptree& tree)
{

}


void SSLICEffect::WriteToXML(const boost::property_tree::ptree& tree)
{

}

}