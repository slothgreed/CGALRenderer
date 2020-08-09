namespace KI
{
namespace Renderer
{
RenderData::RenderData(PRIM_TYPE primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer)
{
	SetGeometryData(primitiveType, pVertexBuffer, pIndexBuffer);
}

RenderData::~RenderData()
{
}

void RenderData::SetShading(shared_ptr<IShading> pShading)
{
	m_pShading = pShading;
}

void RenderData::AddRenderRegion(const string& descriptor, shared_ptr<IShading> pShading, int first, int count)
{
	if (GetPrimitiveType() != PRIM_TYPE_TRIANGLES)
	{
		assert(0);
		return;
	}
	m_pRenderRegion.push_back(RenderRegion());
	int size = (int)m_pRenderRegion.size() - 1;
	m_pRenderRegion[size].m_descriptor = descriptor;
	m_pRenderRegion[size].m_pShading = pShading;
	m_pRenderRegion[size].m_first = first;
	m_pRenderRegion[size].m_count = count;
}

void RenderData::ClearRenderRegion()
{
	m_pRenderRegion.clear();
}

void RenderData::SetGeometryData(PRIM_TYPE primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer)
{
	m_pPrimitiveType = primitiveType;
	m_pVertexBuffer = pVertexBuffer;
	m_pIndexBuffer = pIndexBuffer;
}

void RenderData::DrawUseRegion(const shared_ptr<UniformStruct> pUniform)
{
	// �����}�e���A���ŕ`��
	for (int i = 0; i < m_pRenderRegion.size(); i++)
	{
		Draw(
			m_pShader,
			m_pRenderRegion[i].m_pShading,
			pUniform,
			m_pRenderRegion[i].m_first,
			m_pRenderRegion[i].m_count);
	}

	// �����}�e���A���ȊO��ʏ�}�e���A���ŕ`��E�\�[�g����Ă���O��
	{
		if (m_pRenderRegion[0].m_first != 0)
		{
			Draw(m_pShader, m_pShading, pUniform, 0, m_pRenderRegion[0].m_first);
		}

		int first = 0;
		int count = 0;
		for (int i = 0; i < m_pRenderRegion.size() - 1; i++)
		{
			first = m_pRenderRegion[i].m_first + m_pRenderRegion[i].m_count;
			count = m_pRenderRegion[i + 1].m_first - first;

			Draw(m_pShader, m_pShading, pUniform, first, count);
		}

		int size = (int)m_pRenderRegion.size() - 1;
		first = m_pRenderRegion[size].m_first + m_pRenderRegion[size].m_count;
		count = GetVertexSize() - first;
		if (first != GetVertexSize())
		{
			Draw(m_pShader, m_pShading, pUniform, first, count);
		}
	}
}

int RenderData::GetVertexSize()
{
	if (m_pIndexBuffer == nullptr)
	{
		return m_pVertexBuffer->GetVertexSize();
	}
	else
	{
		return m_pIndexBuffer->Size();
	}
}
void RenderData::Draw(
	shared_ptr<IShader> pShader,
	shared_ptr<IShading> pShading,
	shared_ptr<UniformStruct> pUniform,
	int first, 
	int count)
{
	if (first == -1) {
		first = 0;
	}
	if (count == -1) {
		count = GetVertexSize();
	}

	pShader->Use();
	pShader->Bind(pShading, pUniform);

	if (m_pIndexBuffer == nullptr)
	{
		m_pVertexBuffer->Draw(m_pPrimitiveType, first, count);
	}
	else
	{
		m_pVertexBuffer->DrawByIndexBuffer(m_pPrimitiveType, m_pIndexBuffer.get(), first, count);
	}

	pShader->UnBind(pShading, pUniform);
	pShader->UnUse();
}

void RenderData::FindOrNewShader(shared_ptr<IShading> pShading)
{
	if (pShading->NeedReCompileShader() || m_pShader == nullptr)
	{
		auto pBuildInfo = make_shared<IShaderBuildInfo>();
		pBuildInfo->SetVertexBuffer(m_pVertexBuffer);
		pBuildInfo->SetShaderChunk(pShading);
		m_pShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);
		pShading->CompiledShader();
	}
}

void RenderData::Draw(const shared_ptr<UniformStruct> pUniform)
{
	if (m_pRenderRegion.size() != 0)
	{
		DrawUseRegion(pUniform);
		return;
	}

	if (m_pVertexBuffer == nullptr ||
		m_pShading == nullptr)
	{
		assert(0);
		return;
	}

	FindOrNewShader(m_pShading);
	Draw(m_pShader, m_pShading, pUniform, 0, GetVertexSize());
}

shared_ptr<RenderData> RenderData::Clone()
{
	auto pClone = make_shared<RenderData>();
	pClone->m_pPrimitiveType = m_pPrimitiveType;
	pClone->m_pIndexBuffer	= m_pIndexBuffer;
	pClone->m_pVertexBuffer = m_pVertexBuffer;
	pClone->m_pShading		= m_pShading;

	return pClone;
}
};
}
