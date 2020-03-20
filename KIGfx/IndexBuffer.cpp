namespace KI
{
namespace Gfx
{
IndexBuffer::IndexBuffer()
{
	m_Id = 0;
}

IndexBuffer::~IndexBuffer()
{
	Dispose();
}

void IndexBuffer::Generate()
{
	if (m_Id == 0)
	{
		glGenBuffers(1, &m_Id);
	}
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Set(GLuint primitiveType, const vector<int>& index)
{
	if (IsGenerated() == false)
	{
		Generate();
	}

	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(int), index.data(), GL_STATIC_DRAW);
	// UnBind(); ���̂��s�v
	m_PrimitiveType = primitiveType;
	m_indexSize = (GLuint)index.size();
	Logger::GLError();
}

void IndexBuffer::Dispose()
{
	if (m_Id != 0)
	{
		glDeleteBuffers(1, &m_Id);
	}

	m_Id = 0;
}

void IndexBuffer::Draw()
{
	Bind();
	glDrawElements(m_PrimitiveType, Size(), GL_UNSIGNED_INT, 0);
}
}
}