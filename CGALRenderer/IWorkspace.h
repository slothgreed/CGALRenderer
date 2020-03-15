#ifndef CGAL_RENDERER_INITIALIZER_H
#define	CGAL_RENDERER_INITIALIZER_H

namespace KI
{
class Project;
class IWorkspace
{
public:
	IWorkspace() {};
	virtual ~IWorkspace() {};

public:
	virtual void Initialize(Project* m_pProejct) = 0;
	virtual void Invoke() = 0;
	virtual void ShowProperty() {};
	virtual void ProcessMouseEvent(const MouseInput& input) {};
protected:
	shared_ptr<Mouse> m_pMouse;
	CONTROLER_TYPE m_CurrentController;
	map<CONTROLER_TYPE, IController*> m_pController;
	unique_ptr<CommandManager> m_pCommandManager;

};

}

#endif // CGAL_RENDERER_INITIALIZER_H