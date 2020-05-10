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
	pCamera->LookAt(vec3(0, 0, 2), vec3(0, 0, 0), vec3(0, 1, 0));
	pCamera->Perspective(glm::radians(60.0f), 1, 0.01f, 1000);
	m_pScene->SetCamera(pCamera);

	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER] = new CameraController();
	m_CurrentController = CONTROLER_TYPE::CAMERA_CONTROLER;
	shared_ptr<IControllerArgs> args = make_shared<CameraControllerArgs>(pCamera);
	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER]->SetArgs(args);

	// sphere rendering
	{
		auto sphereData = make_shared<RenderData>();
		ModelGenerator::Sphere(10, 36, 36, sphereData.get());
		
		auto pTexture = make_shared<Texture>();
		pTexture->Generate();
		TextureData textureData;
		//TextureGenerator::RandomTexture(8, 255, textureData);
		TextureGenerator::Load("E:\\cgModel\\texture\\SkyBox\\moon1024.png", textureData);
		//TextureGenerator::Load("E:\\cgModel\\texture\\SkyBox\\earth2048.png", textureData);
		pTexture->Begin();
		pTexture->Set(textureData);
		pTexture->End();
		
		auto pShaderPass = make_shared<DefaultShaderPass>(make_shared<BasicMaterial>(pTexture));
		sphereData->SetShaderPass(pShaderPass);
		auto sphereNode = make_shared<PrimitiveNode>(sphereData);

		
		//m_pScene->AddModelNode(sphereNode);
	}

	// icosahedron rendring
	{
		Icosahedron icosahedron;
		icosahedron.Build(IcosahedronArgs());
		auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
		pVertexBuffer->SetPosition(icosahedron.Position());
		pVertexBuffer->SetNormal(icosahedron.Normal());
		auto pIndexBuffer = make_shared<IndexBuffer>();
		pIndexBuffer->Set(icosahedron.Index());

		auto pRenderData = make_shared<RenderData>();
		pRenderData->SetGeometryData(GL_TRIANGLES, pVertexBuffer, pIndexBuffer);
		auto pPlaneShaderPass = make_shared<DefaultShaderPass>(make_shared<BasicMaterial>(BasicMaterial::BASIC_MATERIAL_TYPE_NORMAL));
		pRenderData->SetShaderPass(pPlaneShaderPass);
		auto pPrimitiveNode = make_shared<PrimitiveNode>(pRenderData);
		//m_pScene->AddModelNode(pPrimitiveNode);
	}

	// quad rendering
	{
		auto pRenderData = make_shared<RenderData>();
		auto pShaderPass = make_shared<DefaultShaderPass>(make_shared<BasicMaterial>(vec4(1, 1, 0, 1)));
		pRenderData->SetShaderPass(pShaderPass);
		ModelGenerator::Plane(pRenderData.get(),VERTEX_LAYOUT_COLOR);
		auto pPlaneNode = make_shared<PrimitiveNode>(
			make_shared<PrimitiveModel>(
				make_shared<Quad>(
					QuadArgs(vec2(-1), vec2(1)))));
		//m_pScene->AddModelNode(pPlaneNode);
	}

	{
		auto pMoveManipulator = make_shared<MoveManipulator>();
		pMoveManipulator->Build();
		auto pManipulatorNode = make_shared<ManipulatorNode>(MANIPULATOR_TYPE_MOVE);
		m_pScene->AddModelNode(pManipulatorNode);

	}

	//BDB bdb(vec3(0), vec3(2));
	//pCamera->FitToBDB(bdb);

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
	else if (input.Event() == MOUSE_EVENT_DOWN)
	{
		if (input.Press(MOUSE_BUTTON_LEFT))
		{
			m_pCommandManager->Execute(
				make_shared<PickCommand>(
					make_shared<PickCommandArgs>(
						GetViewport(),
						m_pScene,
						input.Position())));
		}
	}
}
}