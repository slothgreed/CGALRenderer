
Workspace::Workspace()
{
	
}

Workspace::~Workspace()
{
}

void Workspace::Initialize(Project* m_pProject)
{
	ShaderUtility::SetShaderDirectory(m_pProject->ProjectDir() + "\\Resource");
	ShaderBuildInfo buildInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PC, buildInfo);
	m_pDefaultShader = ShaderManager::Instance()->FindOrNew(buildInfo);
	
	m_pCamera = make_shared<Camera>();
	m_pCamera->LookAt(vec3(0, 0, -2), vec3(0, 0, 0), vec3(0, 1, 0));
	m_pCamera->Perspective(glm::radians(60.0f), 1, 0.01, 1000);

	m_pUniformScene = make_shared<UniformScene>();
	m_pUniformScene->Generate();
	SceneData sceneData;
	sceneData.ViewMatrix = m_pCamera->ViewMatrix();
	sceneData.Projection = m_pCamera->Projection();
	m_pUniformScene->Set(sceneData);

	shared_ptr<CGALPolyhedron> polyhedron = make_shared<CGALPolyhedron>();
	polyhedron->Load("E:\\cgModel\\StanfordBunny.off");
	//m_pPolyhedron->Load("E:\\Tools\\CGAL-5.0-beta1\\build\\examples\\Polygon_mesh_processing\\Debug\\data\\eight.off");
	//m_pPolyhedron->Load("E:\\cgModel\\model\\fandisk\\fandisk.off");

	vector<vec3> facet;
	vector<vec3> normal;
	polyhedron->GetFacetList(facet, normal);
	auto facetBuffer = make_shared<VertexBuffer>();
	facetBuffer->Generate(VERTEX_LAYOUT_PN);
	facetBuffer->SetPosition(GL_TRIANGLES, facet);
	facetBuffer->SetNormal(normal);

	ShaderBuildInfo facetShaderInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PN, facetShaderInfo);
	auto facetShader = ShaderManager::Instance()->FindOrNew(facetShaderInfo);

	BDB bdb;
	polyhedron->GetBDB(bdb);
	m_pCamera->FitToBDB(bdb);

	auto facetNode = make_shared<ModelNode>(facetShader, facetBuffer);
	m_pRenderList.push_back(facetNode);
	facetNode->SetBDB(bdb);

	vector<vec3> edge;
	polyhedron->GetEdgeList(edge);
	auto edgeBuffer = make_shared<VertexBuffer>();
	edgeBuffer->Generate(VERTEX_LAYOUT_P);
	edgeBuffer->SetPosition(GL_LINES, edge);
	
	ShaderBuildInfo edgeShaderInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PN, edgeShaderInfo);
	shared_ptr<IShader> edgeShader = ShaderManager::Instance()->FindOrNew(edgeShaderInfo);

	auto edgeNode = make_shared<ModelNode>(edgeShader, edgeBuffer);
	m_pRenderList.push_back(edgeNode);

	auto axis = make_shared<VertexBuffer>();
	ModelGenerator::Axis(axis.get());
	auto axisNode = make_shared<ModelNode>(m_pDefaultShader, axis);
	m_pRenderList.push_back(axisNode);

}

void Workspace::Invoke()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	SceneData sceneData;
	sceneData.ViewMatrix = m_pCamera->ViewMatrix();
	sceneData.Projection = m_pCamera->Projection();
	m_pUniformScene->Set(sceneData);
	m_pUniformScene->Bind();

	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		m_pRenderList[i]->Draw();
	}
	
	m_pUniformScene->UnBind();
}

void Workspace::ShowProperty()
{
	m_pCamera->ShowProperty();

	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		m_pRenderList[i]->ShowProperty();
	}
}