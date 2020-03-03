
namespace KI
{
GrayScaleEffect::GrayScaleEffect()
{
}

GrayScaleEffect::~GrayScaleEffect()
{
}

void GrayScaleEffect::Initialize()
{
	m_pPlane = make_shared<DefaultVertexBuffer>();
	ModelGenerator::RenderPlane(m_pPlane.get());

	auto shaderDefine = make_shared<GrayScaleShaderDefine>();
	m_pGrayScaleShader = static_pointer_cast<GrayScaleShader>(ShaderManager::Instance()->FindOrNew(shaderDefine));
	int size = 64;
	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, size, size);
}

void GrayScaleEffect::SetTexture(shared_ptr<Texture> texture)
{
	if (m_pGrayUniform == nullptr)
	{
		m_pGrayUniform = make_shared<GrayScaleUniform>();
	}

	m_pGrayUniform->pTexture = texture;
}

void GrayScaleEffect::Resize(int width, int height)
{
	m_pRenderTarget->Resize(width, height);
}
void GrayScaleEffect::Draw()
{
	m_pRenderTarget->Begin();
	m_pRenderTarget->Clear();
	m_pGrayScaleShader->Use();
	m_pGrayScaleShader->Bind(m_pGrayUniform);
	m_pPlane->Draw();
	m_pGrayScaleShader->UnBind();
	m_pGrayScaleShader->UnUse();
	m_pRenderTarget->End();
}

//void GrayScaleEffect::ReadFromXML(const boost::property_tree::ptree& tree)
//{
//
//}
//
//
//void GrayScaleEffect::WriteToXML(const boost::property_tree::ptree& tree)
//{
//
//}

}
