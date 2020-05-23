namespace KI
{
namespace Renderer
{
PfxPlane::PfxPlane(shared_ptr<IMaterial> pMaterial)
{
	m_pMaterial = pMaterial;
	Initialize();
}

PfxPlane::~PfxPlane()
{
}

void PfxPlane::Initialize()
{
	m_pRenderData = make_shared<RenderData>();
	ModelGenerator::Plane(m_pRenderData.get(), VERTEX_LAYOUT_TEXCOORD);
	m_pRenderData->SetMaterial(m_pMaterial);
}
void PfxPlane::Draw()
{
	m_pRenderData->Draw();

	Logger::GLError();
}
}
}
