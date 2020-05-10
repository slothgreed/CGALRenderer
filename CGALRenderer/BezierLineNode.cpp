
namespace KI
{

BezierLineNode::BezierLineNode(shared_ptr<RenderData> pRenderData)
{
	auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_BEZIERLINE);
	auto pMaterial = make_shared<BasicMaterial>(vec4(0, 0, 0, 1));
	pBuildInfo->SetVertexCode(make_shared<DefaultVertexCode>());
	pBuildInfo->SetTESCode(make_shared<BezierLineTESCode>());
	pBuildInfo->SetTCSCode(make_shared<BezierLineTCSCode>());
	pBuildInfo->SetFragCode(make_shared<DefaultFragCode>());
	pBuildInfo->AddEmbeddedCode(pMaterial);
	auto pBezierShader = static_pointer_cast<BezierLineShader>(ShaderManager::Instance()->FindOrNew(pBuildInfo));
	pBezierShader->SetPatchVertices(4);

	auto pTCSUniform = make_shared<BezierLineUniform>();
	auto pShaderPass = make_shared<GeneralShaderPass>();
	pShaderPass->SetShader(pBezierShader);
	pShaderPass->SetMaterial(pMaterial);
	pShaderPass->GetUniform()->Set(nullptr, nullptr, pTCSUniform, nullptr, nullptr);
	pRenderData->SetShaderPass(pShaderPass);
	m_pRenderData = pRenderData;
}

BezierLineNode::~BezierLineNode()
{
}

void BezierLineNode::Draw()
{
	m_pRenderData->Draw();
}

}
