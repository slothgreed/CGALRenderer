Shader::Shader()
{
}

Shader::~Shader()
{
}

void Shader::Build(const ShaderBuildInfo& buildInfo)
{
	string vertexCode;
	string fragCode;
	string version;
	FileIO::Load(buildInfo.versionPath, version);
	FileIO::Load(buildInfo.vertexPath, vertexCode);
	FileIO::Load(buildInfo.fragmentPath, fragCode);

	vertexCode = version + buildInfo.vertexDefine + vertexCode;
	fragCode = version + buildInfo.fragementDefine + fragCode;

	BuildFromCode(vertexCode, fragCode);
}


void Shader::BuildFromCode(const std::string& vertexShaderCode, const std::string& fragmentShader)
{
	m_fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	m_vertexShader = Compile(vertexShaderCode, GL_VERTEX_SHADER);
	m_fragShader =  Compile(fragmentShader, GL_FRAGMENT_SHADER);

	Link(m_vertexShader, m_fragShader);
	BindScene();
}

GLuint Shader::Compile(const std::string& code, GLuint shaderType)
{
	GLuint id = glCreateShader(shaderType);

	const GLchar* sourceCode = code.c_str();
	GLint size = (GLint)code.size();
	glShaderSource(id, 1, &sourceCode, &size);

	glCompileShader(id);
	GLint result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint maxLength = 0;
		// The maxLength includes the NULL character
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* errorLog = new GLchar[maxLength];
		glGetShaderInfoLog(id, maxLength, &maxLength, errorLog);
		Logger::Output(LOG_LEVEL::ERROR, "Shader Compile Error");
	}

	return id;
}

void Shader::Link(GLuint vertexId, GLuint fragId)
{
	m_programId = glCreateProgram();
	glAttachShader(m_programId, vertexId);
	glAttachShader(m_programId, fragId);

	glDeleteShader(vertexId);
	glDeleteShader(fragId);

	glLinkProgram(m_programId);

	GLint result;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint maxLength = 0;
		// The maxLength includes the NULL character
		glGetShaderiv(m_programId, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* errorLog = new GLchar[maxLength];
		glGetShaderInfoLog(m_programId, maxLength, &maxLength, errorLog);
		Logger::Output(LOG_LEVEL::ERROR, "Shader Link Error");
	}
}

void Shader::BindScene()
{
	GLint sceneBlock = glGetUniformBlockIndex(m_programId, "Scene");
	glUniformBlockBinding(m_programId, sceneBlock, SCENE_DATA_LOCATION);
	Logger::GLError();
}

void Shader::Use()
{
	if (m_programId == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "Not call Initialize");
	}

	glUseProgram(m_programId);
}

void Shader::UnUse()
{
	glUseProgram(0);
}