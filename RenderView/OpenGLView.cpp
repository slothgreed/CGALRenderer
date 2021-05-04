#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32

#include "GLFW/glfw3native.h"
#include "imgui_internal.h"
namespace KI
{
namespace RenderView
{
void ScrollCallBack(GLFWwindow* window, double x, double y)
{
	MouseInput input;
	input.SetWheel((int)y);
	input.SetEvent(KI_MOUSE_EVENT::MOUSE_EVENT_WHEEL);
	TheApp()->ProcessMouseEvent(input);
}

void CursorPosCallBack(GLFWwindow* window, double xpos, double ypos)
{
	MouseInput input;
	input.SetPosition((float)xpos, (float)ypos);
	input.SetEvent(KI_MOUSE_EVENT::MOUSE_EVENT_MOVE);

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		input.SetPress(KI_MOUSE_BUTTON::MOUSE_BUTTON_LEFT);
	}
	else
	{
		input.SetRelease(KI_MOUSE_BUTTON::MOUSE_BUTTON_LEFT);
	}

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{
		input.SetPress(KI_MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE);
	}
	else
	{
		input.SetRelease(KI_MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE);
	}

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		input.SetPress(KI_MOUSE_BUTTON::MOUSE_BUTTON_RIGHT);
	}
	else
	{
		input.SetRelease(KI_MOUSE_BUTTON::MOUSE_BUTTON_RIGHT);
	}

	TheApp()->ProcessMouseEvent(input);
}

void WindowSizeCallBack(GLFWwindow* window, int width, int height)
{
	WindowEvent winEvent;
	winEvent.SetEvent(WINDOW_EVENT::WINDOW_EVENT_RESIZE);
	winEvent.SetSize(width, height);
	TheApp()->ProcessWindowEvent(winEvent);
}

void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	KI_MOUSE_BUTTON mouseButton;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		mouseButton = MOUSE_BUTTON_LEFT;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mouseButton = MOUSE_BUTTON_MIDDLE;
		break; 
	case GLFW_MOUSE_BUTTON_RIGHT:
		mouseButton = MOUSE_BUTTON_RIGHT;
		break;
	default:
		break;
	}

	double posX;
	double posY;
	glfwGetCursorPos(window, &posX, &posY);

	MouseInput input;
	input.SetPosition((float)posX, (float)posY);
	if (action == GLFW_PRESS)
	{
		input.SetEvent(MOUSE_EVENT_DOWN);
		input.SetPress(mouseButton);
	}
	else
	{
		input.SetEvent(MOUSE_EVENT_UP);
		input.SetRelease(mouseButton);
	}

	TheApp()->ProcessMouseEvent(input);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{

	}
}

OpenGLView* theApp = NULL;
OpenGLView* TheApp()
{
	if (theApp == NULL)
	{
		Logger::Output(LOG_LEVEL::LOG_LEVEL_ERROR, "Not CGALRendererInitialized");
	}
	return theApp;
}

OpenGLView::OpenGLView()
	:m_pGfxResource(nullptr)
{
}

OpenGLView::~OpenGLView()
{
	FreeLibrary();
}

void DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	string sourceStr;
	string typeStr;
	string severityStr;
	string idStr;
	string messageStr;
	glEx::GetDebugInfoSourceStr(source, &sourceStr);
	glEx::GetDebugInfoTypeStr(type, &typeStr);
	glEx::GetDebugInfoSeverityStr(severity, &severityStr);

	sourceStr = "Source : " + sourceStr + "\n";
	typeStr = "Type : " + typeStr + "\n";
	idStr = "ID : " + to_string(id) + "\n";
	severityStr = "Severity : " + severityStr + "\n";
	messageStr = "Message : " + string(message) + "\n";

	//Logger::Output(LOG_LEVEL_DEBUG, sourceStr + typeStr + idStr + severityStr + messageStr);
}
bool OpenGLView::Initialize()
{
	if (!glfwInit())
	{
		return false;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
	m_window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
	if (m_window == NULL)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	glfwSetCursorPosCallback(m_window, CursorPosCallBack);
	glfwSetMouseButtonCallback(m_window, MouseButtonCallBack);
	glfwSetScrollCallback(m_window, ScrollCallBack);	// mouse wheel;
	glfwSetWindowSizeCallback(m_window, WindowSizeCallBack);
	glfwSetKeyCallback(m_window, KeyCallback);
	glDebugMessageCallback(DebugMessageCallback, NULL);

	SetDeviceContext(glfwGetWin32Window(m_window));
	SetRenderContext(glfwGetWGLContext(m_window));
	
	m_pViewport = make_shared<Viewport>();
	m_pViewport->SetPosition(0, 0);
	m_pViewport->Resize(640, 480);
	theApp = this;

	InitLibrary();
	return true;
}

void OpenGLView::InitLibrary()
{
	InitRenderLibrary();
}

void OpenGLView::FreeLibrary()
{
	FreeRenderLibrary();

	FreeContext();
}

void OpenGLView::FreeContext()
{

	// close GL context and any other GLFW resources
	glfwDestroyWindow(m_window);
	glfwTerminate();

}

void OpenGLView::InitRenderLibrary()
{
	if (m_pGfxResource == nullptr) {
		m_pGfxResource = new GfxResource();
		m_pGfxResource->Initialize();
	}
}

void OpenGLView::FreeRenderLibrary()
{
	if (m_pGfxResource) {
		m_pGfxResource->Dispose();
		RELEASE_INSTANCE(m_pGfxResource);
	}
}

const GfxResource & OpenGLView::GetGfxResource()
{
	return *m_pGfxResource;
}

void OpenGLView::SetViewModel(shared_ptr<ViewViewModel> pViewModel)
{
	m_pViewModel = pViewModel;
	m_pViewModel->SetViewport(m_pViewport);
}

bool OpenGLView::Run()
{
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	
	BufferState bufferState;
	bufferState.ClearColor(vec4(1, 1, 1, 1));
	bufferState.Bind();

	DepthState depthState;
	depthState.DepthTest(true);
	depthState.DepthFunc(COMP_FUNC::COMP_FUNC_LESS);
	depthState.Bind();

	CullState cullState;
	cullState.CullEnable(true);
	cullState.CullFace(CULL_MODE::CULL_MODE_BACK);
	cullState.FrontFace(FRONT_FACE_CCW);
	cullState.Bind();

	PolygonState polyState;
	polyState.OffsetFill(true);
	polyState.Offset(1.0, 1.0);
	polyState.Bind();

	//glEnable(GL_TEXTURE_2D);

	/* OTHER STUFF GOES HERE NEXT */

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 400 core");

	Timer timer;
	timer.Start();
	int m_level = 0;
	//bool show_demo_window = true;
	//bool show_another_window = false;
	//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();
		
		m_pViewModel->Invoke();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		m_pViewModel->ShowUI(ImGui::GetCurrentContext());

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(m_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_window);

		timer.WaitForFPS(60);
	}

	timer.End();
	
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	return true;
}

void OpenGLView::ProcessMouseEvent(const MouseInput& input)
{
	m_pViewModel->ProcessMouseEvent(input);
}

void OpenGLView::ProcessWindowEvent(const WindowEvent& winEvent)
{
	m_pViewport->Resize(winEvent.Size().x, winEvent.Size().y);
	m_pViewModel->WindowResize(winEvent.Size().x, winEvent.Size().y);
}

}
}
