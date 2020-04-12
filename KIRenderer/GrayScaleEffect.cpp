namespace KI
{
namespace Renderer
{
GrayScaleEffect::GrayScaleEffect()
{
}

GrayScaleEffect::~GrayScaleEffect()
{
}

void GrayScaleEffect::Initialize(int width, int height)
{
	m_pPlane = make_shared<DefaultVertexBuffer>();
	ModelGenerator::RenderPlane(m_pPlane.get());

	auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE::SHADER_TYPE_GRAYSCALE);
	pBuildInfo->SetVertexCode(make_shared<PostProcessVertexCode>());
	pBuildInfo->SetFragCode(make_shared<GrayScaleFragCode>());
	m_pGrayScaleShader = static_pointer_cast<GrayScaleShader>(ShaderManager::Instance()->FindOrNew(pBuildInfo));
	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, width, height);

	auto pGrayUniform = make_shared<GrayScaleUniform>();
	m_pGrayUniform = make_shared<UniformSet>(nullptr, pGrayUniform);
}

void GrayScaleEffect::SetTexture(shared_ptr<Texture> pTexture)
{
	if (m_pGrayUniform->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_GRAYSCALE) {
		assert(0);
		return;
	}

	auto uniformParameter = static_pointer_cast<GrayScaleUniform>(m_pGrayUniform->Frag());

	uniformParameter->SetTexture(pTexture);
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
	m_pGrayScaleShader->UnBind(m_pGrayUniform);
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
}