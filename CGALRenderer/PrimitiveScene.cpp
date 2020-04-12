namespace KI
{
PrimitiveScene::~PrimitiveScene()
{
	for (auto itr = m_pController.begin(); itr != m_pController.end(); itr++)
	{
		delete itr->second;
	}
}

void PrimitiveScene::Initialize(Project* m_pProject)
{
	m_pCommandManager = make_unique<CommandManager>();
	m_pMouse = make_shared<Mouse>();

	m_pScene = make_shared<Scene>();
	m_pScene->Initialize();

	auto pCamera = make_shared<PerspectiveCamera>();
	pCamera->LookAt(vec3(0, 0, -2), vec3(0, 0, 0), vec3(0, 1, 0));
	pCamera->Perspective(glm::radians(60.0f), 1, 0.01f, 1000);
	m_pScene->SetCamera(pCamera);

	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER] = new CameraController();
	m_CurrentController = CONTROLER_TYPE::CAMERA_CONTROLER;
	shared_ptr<IControllerArgs> args = make_shared<CameraControllerArgs>(pCamera);
	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER]->SetArgs(args);

	auto sphere = make_shared<DefaultVertexBuffer>();
	auto sphereIdx = make_shared<IndexBuffer>();
	ModelGenerator::Sphere(10, 36, 36, sphere.get(), sphereIdx.get());
	auto pMaterial = make_shared<DefaultMaterial>();
	auto sphereNode = make_shared<PrimitiveNode>(sphere, sphereIdx, pMaterial);

	auto pTexture = make_shared<Texture>();
	pTexture->Generate();
	TextureData textureData;
	//TextureGenerator::RandomTexture(8, 255, textureData);
	TextureGenerator::Load("E:\\cgModel\\texture\\SkyBox\\moon1024.png", textureData);
	//TextureGenerator::Load("E:\\cgModel\\texture\\SkyBox\\earth2048.png", textureData);
	pTexture->Begin();
	pTexture->Set(textureData);
	pTexture->End();
	pMaterial->AddTexture(pTexture);
	m_pScene->AddModelNode(sphereNode);
	BDB bdb(vec3(-10), vec3(10));
	pCamera->FitToBDB(bdb);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);

}
void PrimitiveScene::Invoke()
{
	m_pScene->Bind();
	m_pBackTarget->Begin();
	m_pBackTarget->Clear();
	m_pScene->Draw();
	m_pScene->UnBind();
}

void PrimitiveScene::ProcessMouseEvent(const MouseInput& input)
{
	m_pMouse->ApplyMouseInput(input);
	if (input.Event() == MOUSE_EVENT_WHEEL)
	{
		m_pController[m_CurrentController]->Wheel(*m_pMouse.get());
	}
	else if (input.Event() == MOUSE_EVENT_MOVE)
	{
		m_pController[m_CurrentController]->Move(*m_pMouse.get());
	}
}
}