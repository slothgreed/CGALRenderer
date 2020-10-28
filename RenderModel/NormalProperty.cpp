namespace KI
{
namespace RenderModel
{
NormalProperty::NormalProperty()
{
}

NormalProperty::~NormalProperty()
{
}

void NormalProperty::Build(IModelNode* pModelNode)
{
	m_pShading = make_shared<NormalVisualizeShading>();
	m_pShading->SetLength(5.0f);

	m_pRenderData = make_shared<RenderData>();
	m_pRenderData->SetShading(m_pShading);

	SetVBOData(pModelNode);
}

void NormalProperty::Update(IModelNode* pModelNode)
{
	SetVBOData(pModelNode);
}

void NormalProperty::SetVBOData(IModelNode* pModelNode)
{
	vector<Vertex> vertexList;
	PolygonModelNode* pPolygonModel = nullptr;
	if (IPolygonModel::IsPolygonModel(pModelNode->GetModel()->Type()))
	{
		pPolygonModel = (PolygonModelNode*)pModelNode;
	}
	else
	{
		assert(0);
		return;
	}

	auto pVertexBuffer = pPolygonModel->GetVertexBuffer();
	m_pRenderData->SetGeometryData(PRIM_TYPE_POINTS, pVertexBuffer);
}

void NormalProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	//m_pRenderData->Draw(pUniform);
}
}
}