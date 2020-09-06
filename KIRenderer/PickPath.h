#ifndef PICK_PATH_H
#define	PICK_PATH_H

namespace KI
{
namespace Renderer
{

struct DLL_EXPORT PickResult
{
	int objectID;
	int primitiveID;
};
class DLL_EXPORT PickPath : public IRenderPath
{
public:
	PickPath();
	~PickPath();

	virtual void Initialize(int width, int height) override;
	virtual void Resize(int width, int height) override;
	void Draw(shared_ptr<Scene> pScene);
	void ResetPickID(shared_ptr<Scene> pScene);
	bool GetPickResult(const vec2& position, PickResult* pickResult);
	shared_ptr<RenderTexture> GetPickTexture();

private:
	shared_ptr<IShader> m_pPickShader;
	shared_ptr<RenderTarget> m_pRenderTarget;
};
}
}


#endif PICK_PATH_H