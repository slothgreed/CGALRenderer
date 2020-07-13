namespace KI
{
namespace ShaderLib
{

BezierLineTCSCode::BezierLineTCSCode()
	:IShaderCode(
	string(SHADER_DIRECTORY) +
	string(SHADER_BEZIERLINE) +
	string(SHADER_EXT_TCS))
{
}

BezierLineTCSCode::~BezierLineTCSCode()
{

}

void BezierLineTCSCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(BEZIERLINE_UNIFORM_NUM);
	m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM] = glGetUniformLocation(programId, "numStrips");
	m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM] = glGetUniformLocation(programId, "numSegments");
	Logger::GLError();
}



void BezierLineTCSCode::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = dynamic_cast<BezierLineShading*>(pShaderChunk.get());
	if (pShading->GetPatchVertices() == 0)
	{
		assert(0);
		return;
	}

	glPatchParameteri(GL_PATCH_VERTICES, pShading->GetPatchVertices());

	if (m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM] == -1 ||
		m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM] == -1)
	{
		assert(0);
		return;
	}

	IShaderCode::BindInt(m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM], pShading->StripNum());
	IShaderCode::BindInt(m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM], pShading->SegmentNum());
	
}

void BezierLineTCSCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{

}

void BezierLineShading::SetPatchVertices(GLuint patchVertex)
{
	m_patchVertex = patchVertex;
}

bool BezierLineShading::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pTargetBuffer = dynamic_cast<BezierLineShading*>(pTarget);
	if (pTargetBuffer == nullptr)
	{
		return false;
	}

	return true;
}

shared_ptr<IShaderCode> BezierLineShading::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	switch (type)
	{
	case SHADER_PROGRAM_VERTEX:
		return make_shared<DefaultVertexCode>(pBuildInfo->GetVertexBuffer().get());
	case SHADER_PROGRAM_FRAG:
		return make_shared<BasicFragCode>(BASIC_SHADING_TYPE::BASIC_SHADING_TYPE_FIXCOLOR);
	case SHADER_PROGRAM_TCS:
		return make_shared<BezierLineTCSCode>();
	case SHADER_PROGRAM_TESS:
		return make_shared<BezierLineTESCode>();
	default:
		return nullptr;
	}

	return nullptr;
}
}
}