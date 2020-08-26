#ifndef IGLPICK_H
#define IGLPICK_H

namespace KI
{
namespace Renderer
{
class RenderData;
// Selection Buffer �𗘗p����Picking
class DLL_EXPORT GLPickInfo
{
public:
	GLPickInfo() {};
	~GLPickInfo() {};
	void Set(shared_ptr<RenderData> pRenderData, const vector<vec3>& pPickInfo) { m_pRenderData = pRenderData; m_pPickInfo = pPickInfo; };
	shared_ptr<RenderData> GetRenderData() { return m_pRenderData; };
private:
	shared_ptr<RenderData> m_pRenderData;
	vector<vec3> m_pPickInfo;
};

// uniform id �� primitive id �� pick ����
class DLL_EXPORT IGLPick
{
public:
	IGLPick() {};
	~IGLPick() {};
	
	void Clear() { m_pickId.clear(); }
	virtual void AddPickID(int start, int* next);
	bool HasPickID(int id, int* index);
	int GetPickID(int index);
	virtual void PickDraw(shared_ptr<IShader> pShader, shared_ptr<UniformStruct> pUniformStorage) = 0;
	int Num() { return (int)m_pickId.size(); };

private:
	vector<int> m_pickId;
};

}
}

#endif