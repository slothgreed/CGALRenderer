#include "pch.h"
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
using namespace KI;
TEST(renderTest, Test)
{
	int NEW_SCENE = 4;
	std::cout << "Hello World!\n";
	auto pTexture = new KI::Gfx::Texture();

	//std::unique_ptr<CGALRenderer> renderer(new CGALRenderer());
	//auto pProject = make_shared<Project>();
	//shared_ptr<IWorkspace> pWorkspace;
	//if (NEW_SCENE == 1)
	//{
	//	pWorkspace = make_shared<Workspace>();
	//}
	//else if (NEW_SCENE == 2)
	//{
	//	pWorkspace = make_shared<BunnyScene>();
	//}
	//else if (NEW_SCENE == 3)
	//{
	//	pWorkspace = make_shared<VoronoiScene>();
	//}
	//else if (NEW_SCENE == 4)
	//{
	//	pWorkspace = make_shared<PrimitiveScene>();
	//}
	//else if (NEW_SCENE == 5)
	//{
	//	pWorkspace = make_shared<PfxScene>();
	//}
	//else if (NEW_SCENE == 6)
	//{
	//	pWorkspace = make_shared<TessellationScene>();
	//}
	//else if (NEW_SCENE == 7)
	//{
	//	pWorkspace = make_shared<RungeKuttaScene>();
	//}

	//renderer->Initialize();
	//renderer->SetWorkspace(pWorkspace);
	//pProject->Initialize();
	//pWorkspace->Initialize(pProject.get());

	//renderer->Run();
}