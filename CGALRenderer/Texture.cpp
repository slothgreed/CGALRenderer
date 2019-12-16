namespace KI
{
Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::Generate()
{
	if (m_Id != 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "Already Generated");
	}

	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);

	Logger::GLError();
}

void Texture::Bind()
{
	if (m_Id == 0)
	{
		assert(0);
	}

	glBindTexture(GL_TEXTURE_2D, m_Id);
	Logger::GLError();
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	Logger::GLError();
}

void Texture::Set(const TextureData& data)
{
	Bind();

	glTexImage2D(
		data.target, 
		data.level,
		data.internalformat,
		data.width,
		data.height,
		data.border, 
		data.format,
		data.type,
		data.pixels
	);


	UnBind();

	CopyTextureData(data);

	Logger::GLError();
}

void Texture::CopyTextureData(const TextureData& data)
{
	// pixel 情報は重くなるので保持しない。
	m_data.target	= data.target;
	m_data.level	= data.level;
	m_data.internalformat = data.internalformat;
	m_data.width	= data.width;
	m_data.height	= data.height;
	m_data.border	= data.border;
	m_data.format	= data.format;
	m_data.type		= data.type;
}

void Texture::Dispose()
{
	if (m_Id != 0)
	{
		glDeleteTextures(1, &m_Id);
		m_Id = 0;
	}

	Logger::GLError();
}
}
