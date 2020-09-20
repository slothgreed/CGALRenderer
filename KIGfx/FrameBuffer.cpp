namespace KI
{
namespace Gfx
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
		Logger::Output(LOG_LEVEL::LOG_LEVEL_ERROR, "Already Generated");
	}

	glGenFramebuffers(1, &m_Id);
	Logger::GLError();
}

void FrameBuffer::Bind()
{
	if (m_Id == 0)
	{
		assert(0);
	}

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
	if (m_modifing == false)
	{
		assert(0);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Logger::GLError();
}

bool FrameBuffer::Validate()
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		assert(0);
		return false;
	}

	return true;
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
}