#ifndef PRIMITIVE_SCENE_H
#define	PRIMITIVE_SCENE_H

namespace KI
{
class PrimitiveScene : public IWorkspace
{
public:
	virtual ~PrimitiveScene();
	virtual void Initialize(Project* m_pProejct) override;
	virtual void Invoke() override;
	virtual void ProcessMouseEvent(const MouseInput& input) override;
private:
	void NextModel();
	void PreviewModel();
	void ShowPrimitive(int index);
	shared_ptr<IRenderTarget> m_pBackTarget;
	shared_ptr<Scene> m_pScene;
	int m_currentPrimitive;
};
}
#endif // PRIMITIVE_SCENE_H