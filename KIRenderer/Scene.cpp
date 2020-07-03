namespace KI {
namespace Renderer
{

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
	m_pUniformScene = make_shared<UniformScene>();
	m_pUniformScene->Generate();

	m_pUniformModel = make_shared<UniformModel>();
	m_pUniformModel->Generate();

}

void Scene::AddModelNode(shared_ptr<IModelNode> pModelNode)
{
	m_pRenderList.push_back(pModelNode);
}

void Scene::RemoveModelNode(shared_ptr<IModelNode> pModelNode)
{

}

void Scene::AddLight(shared_ptr<ILight> pLight)
{
	m_pLights.push_back(pLight);
	if (m_pUniformLight == nullptr)
	{
		m_pUniformLight = make_shared<UniformLight>();
		m_pUniformLight->Generate();
	}
}

void Scene::RemoveLight(shared_ptr<ILight> pLight)
{
}

void Scene::Bind()
{
	SceneData sceneData;
	sceneData.viewMatrix = m_pCamera->ViewMatrix();
	sceneData.projection = m_pCamera->Projection();
	m_pUniformScene->Set(sceneData);
	m_pUniformModel->SetViewMatrix(sceneData.viewMatrix);
	m_pUniformScene->Bind();

	if (m_pLights.size() != 0)
	{
		m_pUniformLight->Set(m_pLights[0].get());
		m_pUniformLight->Bind();
	}
}
void Scene::Draw()
{
	shared_ptr<UniformStruct> m_pUniformStruct = make_shared<UniformStruct>();
	m_pUniformStruct->SetLight(m_pUniformLight);
	m_pUniformStruct->SetScene(m_pUniformScene);
	m_pUniformStruct->SetModel(m_pUniformModel);
	vector<IUniform*> pUniform;
	pUniform.push_back(m_pUniformStruct.get());
	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		//m_pRenderList[i]->Draw(pUniform);
	}
}

void Scene::UnBind()
{
	if (m_pUniformLight != nullptr)
	{
		m_pUniformLight->UnBind();
	}

	m_pUniformScene->UnBind();
}

bool SceneModelIterator::HasNext()
{
	if (m_pScene->m_pRenderList.size() > m_Index)
	{
		return true;
	}
	else
	{
		return false;
	}
}

IModelNode& SceneModelIterator::Current()
{
	return *(m_pScene->m_pRenderList[m_Index].get());
}

void SceneModelIterator::Next()
{
	m_Index++;
}

VisibleModelIterator::VisibleModelIterator(Scene* pScene)
	: m_pScene(pScene), m_pNextModel(nullptr), m_NextIndex(0)
{
	Next();	// 1�Ԗڂ̗v�f���擾���Ă����B

}

bool VisibleModelIterator::HasNext()
{
	if (m_pNextModel == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

IModelNode& VisibleModelIterator::Current()
{
	return *m_pNextModel;
}

void VisibleModelIterator::Next()
{
	bool find = false;
	for (int i = m_NextIndex; i < m_pScene->m_pRenderList.size(); i++)
	{
		if (m_pScene->m_pRenderList[i]->Visible())
		{
			m_pNextModel = m_pScene->m_pRenderList[i].get();
			m_NextIndex = i + 1;
			find = true;
			break;
		}
	}

	if (find == false)
	{
		m_pNextModel = nullptr;
	}

}
}
}


