namespace KI
{
namespace Renderer
{
GeometryPath::GeometryPath()
{
}

GeometryPath::~GeometryPath()
{
}

void GeometryPath::Initialize(int width, int height)
{
	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(4, width, height);
}

void GeometryPath::Resize(int width, int height)
{
	m_pRenderTarget->Resize(width, height);
}

void GeometryPath::Draw(const vector<shared_ptr<IModelNode>>& modelNodes)
{
	m_pRenderTarget->Begin();
	m_pRenderTarget->Clear();
	auto pUniform = make_shared<IUniformStorage>();
	for (int i = 0; i < modelNodes.size(); i++)
	{
		modelNodes[i]->Draw(pUniform);
	}

	m_pRenderTarget->End();
}
}
}