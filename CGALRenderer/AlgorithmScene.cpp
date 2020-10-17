namespace KI
{
AlgorithmScene::AlgorithmScene()
{
}

AlgorithmScene::~AlgorithmScene()
{
}

void AlgorithmScene::Initialize()
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

	auto pModel = make_shared<HalfEdgeModel>();
	pModel->Load("E:\\cgModel\\bunny6000.half");
	BDB bdb;
	pModel->GetBDB(bdb);
	m_pScene->GetCamera()->FitToBDB(bdb);
	m_pScene->AddModelNode(make_shared<HalfEdgeDSNode>(pModel));
	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
	
}

void AlgorithmScene::Invoke()
{
	m_pScene->Bind();
	m_pBackTarget->Begin();
	m_pBackTarget->Clear();
	m_pScene->Draw();
	m_pBackTarget->End();
	m_pScene->UnBind();
}

void AlgorithmScene::ProcessMouseEvent(const MouseInput& input)
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
	else if (input.Event() == MOUSE_EVENT_DOWN) 
	{
		if (input.Press(MOUSE_BUTTON_LEFT))
		{
			auto pCommand = make_shared<SmoothingCommand>(
				make_shared<SmoothingCommandArgs>(m_pScene->ModelNodes()[0]));

			m_pCommandManager->Execute(pCommand);
		}
	}
}
}
