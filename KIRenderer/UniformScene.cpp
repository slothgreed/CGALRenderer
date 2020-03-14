namespace KI
{
namespace Renderer
{
UniformScene::UniformScene()
	: UniformBuffer(SCENE_DATA_LOCATION)
{
}

UniformScene::~UniformScene()
{
}


void UniformScene::Set(const SceneData& data)
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(SceneData), &data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	Logger::GLError();
}

}
}