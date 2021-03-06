
namespace KI
{
RungeKuttaScene::RungeKuttaScene()
{
}

RungeKuttaScene::~RungeKuttaScene()
{
}

void RungeKuttaScene::Initialize()
{
	m_pScene = make_shared<Scene>();
	m_pScene->Initialize();
	auto pCamera = make_shared<OrthoCamera>();
	pCamera->LookAt(vec3(0, 0, 1), vec3(0), vec3(0, 1, 0));
	pCamera->Ortho(0, 1, 0, 1, -2, 2);
	m_pScene->SetCamera(pCamera);

	auto pBasicShading = make_shared<BasicShading>(vec4(1, 0, 0, 1));
	auto pPointData = make_shared<RenderData>(PRIM_TYPE_POINTS, make_shared<DefaultVertexBuffer>());
	pPointData->SetShading(pBasicShading);
	m_pPointNode = make_shared<PrimitiveNode>(pPointData);
	m_pScene->AddModelNode(m_pPointNode);

	auto axisNode = make_shared<PrimitiveNode>(make_shared<PrimitiveModel>(make_shared<Axis>(AxisArgs())));
	m_pScene->AddModelNode(axisNode);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
	m_time = 0.0f;
	m_dt = 0.1f;
	InitializePoint();
}

void RungeKuttaScene::InitializePoint()
{
	m_position.resize(256 * 256);
	for (int i = 0; i < m_position.size(); i++)
	{
		m_position[i].x = (Gaccho::rnd(0, 1000) / 1000.0f) + 0.25f;
		m_position[i].y = Gaccho::rnd(0, 1000) / 1000.0f;
		m_position[i].z = 0;
	}

	m_pPointNode->GetVertexBuffer()->SetPosition(m_position);
}

void RungeKuttaScene::Invoke()
{
	m_pBackTarget->Begin();
	m_pBackTarget->Clear();
	Update();
	m_pScene->Bind();
	m_pScene->Draw();
	m_pScene->UnBind();
	m_pBackTarget->End();

	m_time += m_dt;
}

void RungeKuttaScene::Update()
{
	for (int i = 0; i < m_position.size(); i++)
	{
		SampleSimulation::RungeKutta(m_position[i], m_time, m_dt, m_position[i]);
	}

	m_pPointNode->GetVertexBuffer()->SetPosition(m_position);
}

void RungeKuttaScene::ProcessMouseEvent(const MouseInput& input)
{
	if (input.Event() == KI_MOUSE_EVENT::MOUSE_EVENT_DOWN)
	{
		if (input.Press() == KI_MOUSE_BUTTON::MOUSE_BUTTON_RIGHT)
		{
			InitializePoint();
		}
	}
}

}
