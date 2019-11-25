namespace KI
{

FrameBuffer::FrameBuffer()
{
}

FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::Generate()
{
	if (m_Id != 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "Already Generated");
	}

	glGenFramebuffers(1, &m_Id);
	Logger::GLError();
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
	Logger::GLError();
}

void FrameBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	Logger::GLError();
}

void FrameBuffer::Clear()
{
	Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	UnBind();
	Logger::GLError();
}

void FrameBuffer::Dispose()
{
	if (m_Id != 0)
	{
		glDeleteFramebuffers(1, &m_Id);
		m_Id = 0;
	}
	Logger::GLError();
}
}