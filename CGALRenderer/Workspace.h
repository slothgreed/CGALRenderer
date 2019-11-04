#ifndef WORKSPACE_H
#define WORKSPACE_H
class Camera;
class Shader;
class VertexBuffer;
class CGALPolyhedron;
class UniformScene;
class UniformBuffer;
class RenderNode;
class Workspace
{
public:
	Workspace();
	~Workspace();
	void Initialize(Project* m_pProject);
	void Invoke();

	std::shared_ptr<Camera> MainCamera() { return m_pCamera; }
private:

	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Shader> m_pDefaultShader;
	std::shared_ptr<UniformScene> m_pUniformScene;
	
	std::vector<std::shared_ptr<RenderNode>> m_pRenderList;
	
};

#endif WORKSPACE_H