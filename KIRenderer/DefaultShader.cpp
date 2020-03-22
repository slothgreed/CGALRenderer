namespace KI
{
namespace Renderer
{
DefaultShader::DefaultShader()
{
	SetVersion(GLSL_VERSION_400_CORE);
	SetVertexPath(string(SHADER_DIRECTORY) + "\\default.vert");
	SetFragPath(string(SHADER_DIRECTORY) + "\\default.frag");
}

DefaultShader::~DefaultShader()
{
}

void DefaultShader::Initialize()
{
	BindScene();
	BindLight();
	FetchUniformLocation();
}

void DefaultShader::BindScene()
{
	GLint sceneBlock = glGetUniformBlockIndex(m_programId, "SceneData");
	glUniformBlockBinding(m_programId, sceneBlock, SCENE_DATA_LOCATION);
	Logger::GLError();
}

void DefaultShader::BindLight()
{
	GLint lightBlock = glGetUniformBlockIndex(m_programId, "LightData");
	glUniformBlockBinding(m_programId, lightBlock, LIGHT_DATA_LOCATION);
	Logger::GLError();
}

void DefaultShader::FetchUniformLocation()
{
	m_uniformLocation.resize(DEFAULT_UNIFORM_NUM);
	m_uniformLocation[DEFAULT_UNIFORM_COLOR_TEXTURE] = glGetUniformLocation(m_programId, "uTexture0");
	m_uniformLocation[DEFAULT_UNIFORM_FIX_COLOR]	 = glGetUniformLocation(m_programId, "uFixColor");
	Logger::GLError();
}

void DefaultShader::Bind(shared_ptr<IUniform> uniform)
{
	if (uniform == nullptr)
	{
		return;
	}

	if (uniform->Type() == SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		m_uniformParameter = static_pointer_cast<DefaultUniform>(uniform);
	}
	else
	{
		assert(0);
		return;
	}

	DefaultShaderDefine* pDefine = nullptr;
	if (GetShaderDefine()->Type() == SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		pDefine = (DefaultShaderDefine*)GetShaderDefine();
	}
	else
	{
		assert(0);
		return;
	}

	if (pDefine->UseColor() == false &&
		pDefine->UseNormal() == false &&
		pDefine->UseTexcoord() == false)
	{
		BindFixColor();
	}

	if (pDefine->UseTexture0() == true)
	{
		if (m_uniformParameter->GetTexture() == nullptr)
		{
			assert(0);
			return;
		}
		else
		{
			m_uniformParameter->GetTexture()->Begin();
			BindColorTexture();
		}
	}

}

void DefaultShader::UnBind()
{
	if (m_uniformParameter == nullptr)
	{
		return;
	}

	if (m_uniformParameter->GetTexture() != nullptr)
	{
		m_uniformParameter->GetTexture()->End();
	}
}

void DefaultShader::BindColorTexture()
{
	if (m_uniformLocation[DEFAULT_UNIFORM_COLOR_TEXTURE] == -1)
	{
		assert(0);
		return;
	}

	IShader::BindTexture(GL_TEXTURE0, m_uniformLocation[DEFAULT_UNIFORM_COLOR_TEXTURE]);
}

void DefaultShader::BindFixColor()
{
	if (m_uniformLocation[DEFAULT_UNIFORM_FIX_COLOR] == -1)
	{
		assert(0);
		return;
	}

	IShader::BindVector4(m_uniformLocation[DEFAULT_UNIFORM_FIX_COLOR], m_uniformParameter->FixColor());
}

void DefaultShaderDefine::GetDefineCode(SHADER_PROGRAM_TYPE type, string& define)
{
	if (type == SHADER_PROGRAM_TYPE::SHADER_PROGRAM_VERTEX)
	{
		GetVertexDefine(define);
	}
	else if (type == SHADER_PROGRAM_TYPE::SHADER_PROGRAM_FRAG)
	{
		GetFragDefine(define);
	}
}

void DefaultShaderDefine::GetVertexDefine(string& define)
{
	if (m_useNormal)
		define += USE_NORMAL;
	if (m_useColor)
		define += USE_COLOR;
	if (m_useTexcoord)
		define += USE_TEXCOORD;
	if (m_useGBuffer)
		define += USE_GBUFFER;
	if (m_useInstance)
		define += USE_INSTANCE;
}

void DefaultShaderDefine::GetFragDefine(string& define)
{
	if (m_useNormal)
		define += USE_NORMAL;
	if (m_useColor)
		define += USE_COLOR;
	if (m_useTexcoord)
		define += USE_TEXCOORD;
	if (m_useTexture0)
		define += USE_TEXTURE0;
	if (m_useGBuffer)
		define += USE_GBUFFER;
	if (m_useShading)
		define += USE_SHADING;
}

bool DefaultShaderDefine::Compare(IShaderDefine* shaderDefine)
{
	if (shaderDefine->Type() == SHADER_TYPE_DEFAULT)
	{
		DefaultShaderDefine* pDefine = (DefaultShaderDefine*)(shaderDefine);
		if (m_useGBuffer == pDefine->m_useGBuffer &&
			m_useNormal == pDefine->m_useNormal &&
			m_useColor == pDefine->m_useColor &&
			m_useTexcoord == pDefine->m_useTexcoord &&
			m_useTexture0 == pDefine->m_useTexture0 &&
			m_useInstance == pDefine->m_useInstance &&
			m_useShading == pDefine->m_useShading)
		{
			return true;
		}
	}

	return false;
}

void DefaultShaderDefine::SetShaderDefine(GLuint layout)
{
	if (layout & VERTEX_LAYOUT_NORMAL)
	{
		m_useNormal = true;
	}

	if (layout & VERTEX_LAYOUT_COLOR)
	{
		m_useColor = true;
	}

	if (layout & VERTEX_LAYOUT_TEXCOORD)
	{
		m_useTexcoord = true;
		m_useTexture0 = true;
	}

	if (layout & VERTEX_LAYOUT_INSTANCE_MATRIX0 ||
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX1 || 
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX2 || 
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX3)
	{
		m_useInstance = true;
	}
}
}
}