namespace KI
{
namespace Foundation
{

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Output(LOG_LEVEL level, string message)
{
#ifndef _DEBUG
	if (level == LOG_LEVEL::LOG_LEVEL_DEBUG) {
		return;
	}
#endif // _DEBUG

	USE_VAR(level);
	printf(message.data());
	if (level == LOG_LEVEL::LOG_LEVEL_ERROR)
	{
		assert(0);
	}
}

void Logger::GLError()
{
#ifdef _DEBUG
	GLenum result = glGetError();
#else
	GLenum result = GL_NO_ERROR;
#endif // DEBUG

	if (result == GL_NO_ERROR) {
		return;
	}

	switch (result)
	{
	case GL_INVALID_ENUM:
		assert(0);
		break;
	case GL_INVALID_VALUE:
		assert(0);
		break;
	case GL_INVALID_OPERATION:
		assert(0);
		break;
	case GL_STACK_OVERFLOW:
		assert(0);
		break;
	case GL_STACK_UNDERFLOW:
		assert(0);
		break;
	case GL_OUT_OF_MEMORY:
		assert(0);
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		assert(0);
		break;
	default:
		assert(0);
		break;
	}
}
}
}